#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

#include "dingoo.h"

#define SCR_WIDTH 320
#define SCR_HEIGHT 240

#define DEPTH 16

#define STEP 0.1
#define BACK -1.0
#define SCROLLSTEP 5

#define MINIMUM_ARGC 2


#define VERSION_NUMBER 0.1


#ifdef mips
#define KEY_UP  DINGOO_BUTTON_UP
#define KEY_DOWN DINGOO_BUTTON_DOWN
#define KEY_LEFT DINGOO_BUTTON_LEFT
#define KEY_RIGHT DINGOO_BUTTON_RIGHT
#define KEY_PGDOWN DINGOO_BUTTON_B
#define KEY_PGUP DINGOO_BUTTON_X
#define KEY_ZOOM DINGOO_BUTTON_R
#define KEY_UNZOOM DINGOO_BUTTON_L
#define KEY_FOREXIT1 DINGOO_BUTTON_START
#define KEY_FOREXIT2 DINGOO_BUTTON_SELECT
#define KEY_LF DINGOO_BUTTON_Y
#define KEY_FINESCROLL DINGOO_BUTTON_A
#endif

#ifdef x86
#define KEY_UP  DINGOO_BUTTON_UP
#define KEY_DOWN DINGOO_BUTTON_DOWN
#define KEY_LEFT DINGOO_BUTTON_LEFT
#define KEY_RIGHT DINGOO_BUTTON_RIGHT
#define KEY_PGDOWN DINGOO_BUTTON_B
#define KEY_PGUP DINGOO_BUTTON_X
#define KEY_ZOOM DINGOO_BUTTON_R
#define KEY_UNZOOM DINGOO_BUTTON_L
#define KEY_FOREXIT1 DINGOO_BUTTON_START
#define KEY_FOREXIT2 DINGOO_BUTTON_SELECT
#define KEY_LF DINGOO_BUTTON_Y
#define KEY_FINESCROLL DINGOO_BUTTON_A
#endif


#endif // DEFINES_H_INCLUDED
