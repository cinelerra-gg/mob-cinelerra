/*
 * Simple IDCT (Alpha optimized)
 *
 * Copyright (c) 2001 Michael Niedermayer <michaelni@gmx.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * based upon some outcommented c code from mpeg2dec (idct_mmx.c
 * written by Aaron Holtzman <aholtzma@ess.engr.uvic.ca>)
 *
 * Alpha optimiziations by M�ns Rullg�rd <mru@users.sourceforge.net>
 *                     and Falk Hueffner <falk@debian.org>
 */

#include "asm.h"
#include "../dsputil.h"

extern void (*put_pixels_clamped_axp_p)(const DCTELEM *block, uint8_t *pixels,
                                        int line_size);
extern void (*add_pixels_clamped_axp_p)(const DCTELEM *block, uint8_t *pixels, 
                                        int line_size);

// cos(i * M_PI / 16) * sqrt(2) * (1 << 14)
// W4 is actually exactly 16384, but using 16383 works around
// accumulating rounding errors for some encoders
#define W1 ((int_fast32_t) 22725)
#define W2 ((int_fast32_t) 21407)
#define W3 ((int_fast32_t) 19266)
#define W4 ((int_fast32_t) 16383)
#define W5 ((int_fast32_t) 12873)
#define W6 ((int_fast32_t)  8867)
#define W7 ((int_fast32_t)  4520)
#define ROW_SHIFT 11
#define COL_SHIFT 20

/* 0: all entries 0, 1: only first entry nonzero, 2: otherwise  */
static inline int idct_row(DCTELEM *row)
{
    int_fast32_t a0, a1, a2, a3, b0, b1, b2, b3, t;
    uint64_t l, r;
    l = ldq(row);
    r = ldq(row + 4);

    if (l == 0 && r == 0)
        return 0;
    
    a0 = W4 * sextw(l) + (1 << (ROW_SHIFT - 1));

    if (((l & ~0xffffUL) | r) == 0) {
        a0 >>= ROW_SHIFT;
        a0 = (uint16_t) a0;
        a0 |= a0 << 16;
        a0 |= a0 << 32;
        
        stq(a0, row);
        stq(a0, row + 4);
        return 1;
    }

    a1 = a0;
    a2 = a0;
    a3 = a0;

    t = extwl(l, 4);            /* row[2] */
    if (t != 0) {
        t = sextw(t);
        a0 += W2 * t;
        a1 += W6 * t;
        a2 -= W6 * t;
        a3 -= W2 * t;
    }

    t = extwl(r, 0);            /* row[4] */
    if (t != 0) {
        t = sextw(t);
        a0 += W4 * t;
        a1 -= W4 * t;
        a2 -= W4 * t;
        a3 += W4 * t;
    }

    t = extwl(r, 4);            /* row[6] */
    if (t != 0) {
        t = sextw(t);
        a0 += W6 * t;
        a1 -= W2 * t;
        a2 += W2 * t;
        a3 -= W6 * t;
    }

    t = extwl(l, 2);            /* row[1] */
    if (t != 0) {
        t = sextw(t);
        b0 = W1 * t;
        b1 = W3 * t;
        b2 = W5 * t;
        b3 = W7 * t;
    } else {
        b0 = 0;
        b1 = 0;
        b2 = 0;
        b3 = 0;
    }

    t = extwl(l, 6);            /* row[3] */
    if (t) {
        t = sextw(t);
        b0 += W3 * t;
        b1 -= W7 * t;
        b2 -= W1 * t;
        b3 -= W5 * t;
    }

    
    t = extwl(r, 2);            /* row[5] */
    if (t) {
        t = sextw(t);
        b0 += W5 * t;
        b1 -= W1 * t;
        b2 += W7 * t;
        b3 += W3 * t;
    }

    t = extwl(r, 6);            /* row[7] */
    if (t) {
        t = sextw(t);
        b0 += W7 * t;
        b1 -= W5 * t;
        b2 += W3 * t;
        b3 -= W1 * t;
    }

    row[0] = (a0 + b0) >> ROW_SHIFT;
    row[1] = (a1 + b1) >> ROW_SHIFT;
    row[2] = (a2 + b2) >> ROW_SHIFT;
    row[3] = (a3 + b3) >> ROW_SHIFT;
    row[4] = (a3 - b3) >> ROW_SHIFT;
    row[5] = (a2 - b2) >> ROW_SHIFT;
    row[6] = (a1 - b1) >> ROW_SHIFT;
    row[7] = (a0 - b0) >> ROW_SHIFT;

    return 2;
}

static inline void idct_col(DCTELEM *col)
{
    int_fast32_t a0, a1, a2, a3, b0, b1, b2, b3;

    col[0] += (1 << (COL_SHIFT - 1)) / W4;

    a0 = W4 * col[8 * 0];
    a1 = W4 * col[8 * 0];
    a2 = W4 * col[8 * 0];
    a3 = W4 * col[8 * 0];

    if (col[8 * 2]) {
        a0 += W2 * col[8 * 2];
        a1 += W6 * col[8 * 2];
        a2 -= W6 * col[8 * 2];
        a3 -= W2 * col[8 * 2];
    }

    if (col[8 * 4]) {
        a0 += W4 * col[8 * 4];
        a1 -= W4 * col[8 * 4];
        a2 -= W4 * col[8 * 4];
        a3 += W4 * col[8 * 4];
    }

    if (col[8 * 6]) {
        a0 += W6 * col[8 * 6];
        a1 -= W2 * col[8 * 6];
        a2 += W2 * col[8 * 6];
        a3 -= W6 * col[8 * 6];
    }

    if (col[8 * 1]) {
        b0 = W1 * col[8 * 1];
        b1 = W3 * col[8 * 1];
        b2 = W5 * col[8 * 1];
        b3 = W7 * col[8 * 1];
    } else {
        b0 = 0;
        b1 = 0;
        b2 = 0;
        b3 = 0;
    }

    if (col[8 * 3]) {
        b0 += W3 * col[8 * 3];
        b1 -= W7 * col[8 * 3];
        b2 -= W1 * col[8 * 3];
        b3 -= W5 * col[8 * 3];
    }

    if (col[8 * 5]) {
        b0 += W5 * col[8 * 5];
        b1 -= W1 * col[8 * 5];
        b2 += W7 * col[8 * 5];
        b3 += W3 * col[8 * 5];
    }

    if (col[8 * 7]) {
        b0 += W7 * col[8 * 7];
        b1 -= W5 * col[8 * 7];
        b2 += W3 * col[8 * 7];
        b3 -= W1 * col[8 * 7];
    }

    col[8 * 0] = (a0 + b0) >> COL_SHIFT;
    col[8 * 7] = (a0 - b0) >> COL_SHIFT;
    col[8 * 1] = (a1 + b1) >> COL_SHIFT;
    col[8 * 6] = (a1 - b1) >> COL_SHIFT;
    col[8 * 2] = (a2 + b2) >> COL_SHIFT;
    col[8 * 5] = (a2 - b2) >> COL_SHIFT;
    col[8 * 3] = (a3 + b3) >> COL_SHIFT;
    col[8 * 4] = (a3 - b3) >> COL_SHIFT;
}

/* If all rows but the first one are zero after row transformation,
   all rows will be identical after column transformation.  */
static inline void idct_col2(DCTELEM *col)
{
    int i;
    uint64_t l, r;
    uint64_t *lcol = (uint64_t *) col;

    for (i = 0; i < 8; ++i) {
        int_fast32_t a0 = col[0] + (1 << (COL_SHIFT - 1)) / W4;

        a0 *= W4;
        col[0] = a0 >> COL_SHIFT;
        ++col;
    }

    l = lcol[0];
    r = lcol[1];
    lcol[ 2] = l; lcol[ 3] = r;
    lcol[ 4] = l; lcol[ 5] = r;
    lcol[ 6] = l; lcol[ 7] = r;
    lcol[ 8] = l; lcol[ 9] = r;
    lcol[10] = l; lcol[11] = r;
    lcol[12] = l; lcol[13] = r;
    lcol[14] = l; lcol[15] = r;
}

void simple_idct_axp(DCTELEM *block)
{

    int i;
    int rowsZero = 1;           /* all rows except row 0 zero */
    int rowsConstant = 1;       /* all rows consist of a constant value */

    for (i = 0; i < 8; i++) {
        int sparseness = idct_row(block + 8 * i);

        if (i > 0 && sparseness > 0)
            rowsZero = 0;
        if (sparseness == 2)
            rowsConstant = 0;
    }

    if (rowsZero) {
        idct_col2(block);
    } else if (rowsConstant) {
        uint64_t *lblock = (uint64_t *) block;

        idct_col(block);
        for (i = 0; i < 8; i += 2) {
            uint64_t v = (uint16_t) block[i * 8];
            uint64_t w = (uint16_t) block[i * 8 + 8];

            v |= v << 16;
            w |= w << 16;
            v |= v << 32;
            w |= w << 32;
            lblock[0] = v;
            lblock[1] = v;
            lblock[2] = w;
            lblock[3] = w;
            lblock += 4;
        }
    } else {
        for (i = 0; i < 8; i++)
            idct_col(block + i);
    }
}

void simple_idct_put_axp(uint8_t *dest, int line_size, DCTELEM *block)
{
    simple_idct_axp(block);
    put_pixels_clamped_axp_p(block, dest, line_size);
}

void simple_idct_add_axp(uint8_t *dest, int line_size, DCTELEM *block)
{
    simple_idct_axp(block);
    add_pixels_clamped_axp_p(block, dest, line_size);
}