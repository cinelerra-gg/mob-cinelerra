#ifndef EDL_INC
#define EDL_INC

class EDL;

// Load flags for undo
#define LOAD_ALL        0xffffffff
#define LOAD_EDITS      0x00000001
#define LOAD_AUTOMATION 0x00000002
#define LOAD_PATCHES 	0x00000004
#define LOAD_CONSOLE 	0x00000008
#define LOAD_TIMEBAR 	0x00000010
#define LOAD_ACONFIG 	0x00000020
#define LOAD_VCONFIG 	0x00000040
#define LOAD_ASSETS 	0x00000080
#define LOAD_SESSION	0x00000100


#define EDITING_MODES 2

// Editing modes
#define EDITING_ARROW 0
#define EDITING_IBEAM 1



#define EDIT_HANDLE_MODES 3

// Behavior for the edit handles based on mouse button
#define MOVE_ALL_EDITS 0
#define MOVE_ONE_EDIT 1
#define MOVE_NO_EDITS 2
#define MOVE_EDITS_DISABLED 3


// Mandatory folders
#define AEFFECT_FOLDER "Audio Effects"
#define VEFFECT_FOLDER "Video Effects"
#define ATRANSITION_FOLDER "Audio Transitions"
#define VTRANSITION_FOLDER "Video Transitions"

// Default folders
#define CLIP_FOLDER "Clips"
#define MEDIA_FOLDER "Media"



#define AWINDOW_MODES 2
// Modes for AWindow views
#define ASSETS_TEXT 0
#define ASSETS_ICONS 1
#define FOLDERS_TEXT 0
#define FOLDERS_ICONS 1

#define ASSET_COLUMNS 2

// Active tool in CWindow corresponds to a member of the CPanel array
// and the current drag operation

#define CPANEL_OPERATIONS 8


#define CWINDOW_NONE -1
#define CWINDOW_PROTECT     0
#define CWINDOW_ZOOM        1
#define CWINDOW_MASK        2
#define CWINDOW_CAMERA      3
#define CWINDOW_PROJECTOR   4
#define CWINDOW_CROP        5
#define CWINDOW_TOOL_WINDOW 6
#define CWINDOW_TITLESAFE   7

// Current dragging operations not available in the CPanel
#define CWINDOW_SCROLL 0x10
#define CWINDOW_CAMERA_CONTROL_IN 0x11
#define CWINDOW_CAMERA_CONTROL_OUT 0x12
#define CWINDOW_PROJECTOR_CONTROL_IN 0x13
#define CWINDOW_PROJECTOR_CONTROL_OUT 0x14
#define CWINDOW_MASK_CONTROL_IN 0x15
#define CWINDOW_MASK_CONTROL_OUT 0x16
#define CWINDOW_MASK_TRANSLATE 0x17

// Inclusive limits for zoom panel
#define MIN_ZOOM_TIME 1
#define MAX_ZOOM_TIME 0x100000
#define MIN_AMP_ZOOM 8
#define MAX_AMP_ZOOM 262144
#define MIN_TRACK_ZOOM 32
#define MAX_TRACK_ZOOM 1024

#endif