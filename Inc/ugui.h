/* -------------------------------------------------------------------------------- */
/* -- µGUI - Generic GUI module (C)Achim Döbler, 2015                            -- */
/* -------------------------------------------------------------------------------- */
// µGUI is a generic GUI module for embedded systems.
// This is a free software that is open for education, research and commercial
// developments under license policy of following terms.
//
//  Copyright (C) 2015, Achim Döbler, all rights reserved.
//  URL: http://www.embeddedlightning.com/
//
// * The µGUI module is a free software and there is NO WARRANTY.
// * No restriction on use. You can use, modify and redistribute it for
//   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
// * Redistributions of source code must retain the above copyright notice.
//
/* -------------------------------------------------------------------------------- */
/* -- REVISION HISTORY                                                           -- */
/* -------------------------------------------------------------------------------- */
//  Mar 18, 2015  V0.3  Driver support added.
//                      Window and object support added.
//                      Touch support added.
//                      Fixed some minor bugs.
//
//  Oct 20, 2014  V0.2  Function UG_DrawRoundFrame() added.
//                      Function UG_FillRoundFrame() added.
//                      Function UG_DrawArc() added.
//                      Fixed some minor bugs.
//
//  Oct 11, 2014  V0.1  First release.
/* -------------------------------------------------------------------------------- */

#ifndef __UGUI_H
#define __UGUI_H

#include "stdint.h"

/* -------------------------------------------------------------------------------- */
/* -- CONFIG SECTION                                                             -- */
/* -------------------------------------------------------------------------------- */

/* Enable needed fonts here */
//#define  USE_FONT_4X6
//#define  USE_FONT_5X8
//#define  USE_FONT_5X12
//#define  USE_FONT_6X8
//#define  USE_FONT_6X10
//#define  USE_FONT_7X12
//#define  USE_FONT_8X8
//#define  USE_FONT_8X12
//#define USE_FONT_8X12_KRPM
#define  USE_FONT_8X14
//#define  USE_FONT_10X16
//#define  USE_FONT_12X16
//#define  USE_FONT_12X20
//#define  USE_FONT_16X26
//#define  USE_FONT_20X32
//#define  USE_FONT_22X36
//#define  USE_FONT_24X40
//#define  USE_FONT_32X53

/* Specify platform-dependent integer types here */

#define __UG_CONST   const
typedef uint8_t      UG_U8;
typedef int8_t       UG_S8;
typedef uint16_t     UG_U16;
typedef int16_t      UG_S16;
typedef uint32_t     UG_U32;
typedef int32_t      UG_S32;


/* Example for dsPIC33
typedef unsigned char         UG_U8;
typedef signed char           UG_S8;
typedef unsigned int          UG_U16;
typedef signed int            UG_S16;
typedef unsigned long int     UG_U32;
typedef signed long int       UG_S32;
*/

/* -------------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------- */




/* -------------------------------------------------------------------------------- */
/* -- µGUI FONTS                                                                 -- */
/* -- Source: http://www.mikrocontroller.net/user/show/benedikt                  -- */
/* -------------------------------------------------------------------------------- */
typedef struct
{
   unsigned char* p;
   uint8_t* LUT;
   UG_S16 char_width;
   UG_S16 char_height;
} UG_FONT;

#ifdef USE_FONT_4X6
   extern const UG_FONT FONT_4X6;
#endif
#ifdef USE_FONT_5X8
   extern const UG_FONT FONT_5X8;
#endif
#ifdef USE_FONT_5X12
   extern const UG_FONT FONT_5X12;
#endif
#ifdef USE_FONT_6X8
   extern const UG_FONT FONT_6X8;
#endif
#ifdef USE_FONT_6X10
   extern const UG_FONT FONT_6X10;
#endif
#ifdef USE_FONT_7X12
   extern const UG_FONT FONT_7X12;
#endif
#ifdef USE_FONT_8X8
   extern const UG_FONT FONT_8X8;
#endif
#ifdef USE_FONT_8X12_KRPM
   extern const UG_FONT FONT_8X12_KRPM;
#endif
#ifdef USE_FONT_8X12
   extern const UG_FONT FONT_8X12;
#endif
#ifdef USE_FONT_8X14
   extern const UG_FONT FONT_8X14;
#endif
#ifdef USE_FONT_10X16
   extern const UG_FONT FONT_10X16;
#endif
#ifdef USE_FONT_12X16
   extern const UG_FONT FONT_12X16;
#endif
#ifdef USE_FONT_12X20
   extern const UG_FONT FONT_12X20;
#endif
#ifdef USE_FONT_16X26
   extern const UG_FONT FONT_16X26;
#endif
#ifdef USE_FONT_20X32
   extern const UG_FONT FONT_20X32;
#endif
#ifdef USE_FONT_22X36
   extern const UG_FONT FONT_22X36;
#endif
#ifdef USE_FONT_24X40
   extern const UG_FONT FONT_24X40;
#endif
#ifdef USE_FONT_32X53
   extern const UG_FONT FONT_32X53;
#endif

/* -------------------------------------------------------------------------------- */
/* -- TYPEDEFS                                                                   -- */
/* -------------------------------------------------------------------------------- */
typedef struct S_OBJECT                               UG_OBJECT;
typedef struct S_WINDOW                               UG_WINDOW;
typedef UG_S8                                         UG_RESULT;
typedef UG_U32                                        UG_COLOR;
/* -------------------------------------------------------------------------------- */
/* -- DEFINES                                                                    -- */
/* -------------------------------------------------------------------------------- */
#ifndef NULL
   #define NULL ((void*) 0)
#endif

/* Alignments */
#define ALIGN_H_LEFT                                  (1<<0)
#define ALIGN_H_CENTER                                (1<<1)
#define ALIGN_H_RIGHT                                 (1<<2)
#define ALIGN_V_TOP                                   (1<<3)
#define ALIGN_V_CENTER                                (1<<4)
#define ALIGN_V_BOTTOM                                (1<<5)
#define ALIGN_BOTTOM_RIGHT                            (ALIGN_V_BOTTOM|ALIGN_H_RIGHT)
#define ALIGN_BOTTOM_CENTER                           (ALIGN_V_BOTTOM|ALIGN_H_CENTER)
#define ALIGN_BOTTOM_LEFT                             (ALIGN_V_BOTTOM|ALIGN_H_LEFT)
#define ALIGN_CENTER_RIGHT                            (ALIGN_V_CENTER|ALIGN_H_RIGHT)
#define ALIGN_CENTER                                  (ALIGN_V_CENTER|ALIGN_H_CENTER)
#define ALIGN_CENTER_LEFT                             (ALIGN_V_CENTER|ALIGN_H_LEFT)
#define ALIGN_TOP_RIGHT                               (ALIGN_V_TOP|ALIGN_H_RIGHT)
#define ALIGN_TOP_CENTER                              (ALIGN_V_TOP|ALIGN_H_CENTER)
#define ALIGN_TOP_LEFT                                (ALIGN_V_TOP|ALIGN_H_LEFT)

/* Default IDs */
#define OBJ_ID_0                                      0
#define OBJ_ID_1                                      1
#define OBJ_ID_2                                      2
#define OBJ_ID_3                                      3
#define OBJ_ID_4                                      4
#define OBJ_ID_5                                      5
#define OBJ_ID_6                                      6
#define OBJ_ID_7                                      7
#define OBJ_ID_8                                      8
#define OBJ_ID_9                                      9
#define OBJ_ID_10                                     10
#define OBJ_ID_11                                     11
#define OBJ_ID_12                                     12
#define OBJ_ID_13                                     13
#define OBJ_ID_14                                     14
#define OBJ_ID_15                                     15
#define OBJ_ID_16                                     16
#define OBJ_ID_17                                     17
#define OBJ_ID_18                                     18
#define OBJ_ID_19                                     19

/* -------------------------------------------------------------------------------- */
/* -- FUNCTION RESULTS                                                           -- */
/* -------------------------------------------------------------------------------- */
#define UG_RESULT_FAIL                               -1
#define UG_RESULT_OK                                  0

/* -------------------------------------------------------------------------------- */
/* -- UNIVERSAL STRUCTURES                                                       -- */
/* -------------------------------------------------------------------------------- */
/* Area structure */
typedef struct
{
   UG_S16 xs;
   UG_S16 ys;
   UG_S16 xe;
   UG_S16 ye;
} UG_AREA;

/* Text structure */
typedef struct
{
   char* str;
   const UG_FONT* font;
   UG_AREA a;
   UG_COLOR fc;
   UG_COLOR bc;
   UG_U8 align;
   UG_S16 h_space;
   UG_S16 v_space;
} UG_TEXT;

/* -------------------------------------------------------------------------------- */
/* -- BITMAP                                                                     -- */
/* -------------------------------------------------------------------------------- */
typedef struct
{
   void* p;
   UG_U16 width;
   UG_U16 height;
   UG_U8 bpp;
   UG_U8 colors;
} UG_BMP;

#define BMP_BPP_1                                     (1<<0)
#define BMP_BPP_2                                     (1<<1)
#define BMP_BPP_4                                     (1<<2)
#define BMP_BPP_8                                     (1<<3)
#define BMP_BPP_16                                    (1<<4)
#define BMP_BPP_32                                    (1<<5)
#define BMP_RGB888                                    (1<<0)
#define BMP_RGB565                                    (1<<1)
#define BMP_RGB555                                    (1<<2)

/* -------------------------------------------------------------------------------- */
/* -- MESSAGE                                                                    -- */
/* -------------------------------------------------------------------------------- */
/* Message structure */
typedef struct
{
   UG_U8 type;
   UG_U8 id;
   UG_U8 sub_id;
   UG_U8 event;
   void* src;
} UG_MESSAGE;

/* Message types */
#define MSG_TYPE_NONE                                 0
#define MSG_TYPE_WINDOW                               1
#define MSG_TYPE_OBJECT                               2

/* -------------------------------------------------------------------------------- */
/* -- TOUCH                                                                      -- */
/* -------------------------------------------------------------------------------- */
/* Touch structure */
typedef struct
{
   UG_U8 state;
   UG_S16 xp;
   UG_S16 yp;
} UG_TOUCH;


#define TOUCH_STATE_PRESSED                           1
#define TOUCH_STATE_RELEASED                          0

/* -------------------------------------------------------------------------------- */
/* -- OBJECTS                                                                    -- */
/* -------------------------------------------------------------------------------- */
/* Object structure */
struct S_OBJECT
{
   UG_U8 state;                              /* object state                               */
   UG_U8 touch_state;                        /* object touch state                         */
   void (*update) (UG_WINDOW*,UG_OBJECT*);   /* pointer to object-specific update function */
   UG_AREA a_abs;                            /* absolute area of the object                */
   UG_AREA a_rel;                            /* relative area of the object                */
   UG_U8 type;                               /* object type                                */
   UG_U8 id;                                 /* object ID                                  */
   UG_U8 event;                              /* object-specific events                     */
   void* data;                               /* pointer to object-specific data            */
};

/* Currently supported objects */
#define OBJ_TYPE_NONE                                 0
#define OBJ_TYPE_BUTTON                               1
#define OBJ_TYPE_TEXTBOX                              2
#define OBJ_TYPE_IMAGE                                3

/* Standard object events */
#define OBJ_EVENT_NONE                                0
#define OBJ_EVENT_CLICKED                             1

/* Object states */
#define OBJ_STATE_FREE                                (1<<0)
#define OBJ_STATE_VALID                               (1<<1)
#define OBJ_STATE_BUSY                                (1<<2)
#define OBJ_STATE_VISIBLE                             (1<<3)
#define OBJ_STATE_ENABLE                              (1<<4)
#define OBJ_STATE_UPDATE                              (1<<5)
#define OBJ_STATE_REDRAW                              (1<<6)
#define OBJ_STATE_TOUCH_ENABLE                        (1<<7)
#define OBJ_STATE_INIT                                (OBJ_STATE_FREE | OBJ_STATE_VALID)

/* Object touch states */
#define OBJ_TOUCH_STATE_CHANGED                       (1<<0)
#define OBJ_TOUCH_STATE_PRESSED_ON_OBJECT             (1<<1)
#define OBJ_TOUCH_STATE_PRESSED_OUTSIDE_OBJECT        (1<<2)
#define OBJ_TOUCH_STATE_RELEASED_ON_OBJECT            (1<<3)
#define OBJ_TOUCH_STATE_RELEASED_OUTSIDE_OBJECT       (1<<4)
#define OBJ_TOUCH_STATE_IS_PRESSED_ON_OBJECT          (1<<5)
#define OBJ_TOUCH_STATE_IS_PRESSED                    (1<<6)
#define OBJ_TOUCH_STATE_CLICK_ON_OBJECT               (1<<7)
#define OBJ_TOUCH_STATE_INIT                          0

/* -------------------------------------------------------------------------------- */
/* -- WINDOW                                                                     -- */
/* -------------------------------------------------------------------------------- */
/* Title structure */
typedef struct
{
   char* str;
   const UG_FONT* font;
   UG_S8 h_space;
   UG_S8 v_space;
   UG_U8 align;
   UG_COLOR fc;
   UG_COLOR bc;
   UG_COLOR ifc;
   UG_COLOR ibc;
   UG_U8 height;
} UG_TITLE;

/* Window structure */
struct S_WINDOW
{
   UG_U8 objcnt;
   UG_OBJECT* objlst;
   UG_U8 state;
   UG_COLOR fc;
   UG_COLOR bc;
   UG_S16 xs;
   UG_S16 ys;
   UG_S16 xe;
   UG_S16 ye;
   UG_U8 style;
   UG_TITLE title;
   void (*cb)( UG_MESSAGE* );
};

/* Window states */
#define WND_STATE_FREE                                (1<<0)
#define WND_STATE_VALID                               (1<<1)
#define WND_STATE_BUSY                                (1<<2)
#define WND_STATE_VISIBLE                             (1<<3)
#define WND_STATE_ENABLE                              (1<<4)
#define WND_STATE_UPDATE                              (1<<5)
#define WND_STATE_REDRAW_TITLE                        (1<<6)

/* Window styles */
#define WND_STYLE_2D                                  (0<<0)
#define WND_STYLE_3D                                  (1<<0)
#define WND_STYLE_HIDE_TITLE                          (0<<1)
#define WND_STYLE_SHOW_TITLE                          (1<<1)

/* -------------------------------------------------------------------------------- */
/* -- BUTTON OBJECT                                                              -- */
/* -------------------------------------------------------------------------------- */
/* Button structure */
typedef struct
{
   UG_U8 state;
   UG_U8 style;
   UG_COLOR fc;
   UG_COLOR bc;
   UG_COLOR afc;
   UG_COLOR abc;
   const UG_FONT* font;
   char* str;
}UG_BUTTON;

/* Default button IDs */
#define BTN_ID_0                                      OBJ_ID_0
#define BTN_ID_1                                      OBJ_ID_1
#define BTN_ID_2                                      OBJ_ID_2
#define BTN_ID_3                                      OBJ_ID_3
#define BTN_ID_4                                      OBJ_ID_4
#define BTN_ID_5                                      OBJ_ID_5
#define BTN_ID_6                                      OBJ_ID_6
#define BTN_ID_7                                      OBJ_ID_7
#define BTN_ID_8                                      OBJ_ID_8
#define BTN_ID_9                                      OBJ_ID_9
#define BTN_ID_10                                     OBJ_ID_10
#define BTN_ID_11                                     OBJ_ID_11
#define BTN_ID_12                                     OBJ_ID_12
#define BTN_ID_13                                     OBJ_ID_13
#define BTN_ID_14                                     OBJ_ID_14
#define BTN_ID_15                                     OBJ_ID_15
#define BTN_ID_16                                     OBJ_ID_16
#define BTN_ID_17                                     OBJ_ID_17
#define BTN_ID_18                                     OBJ_ID_18
#define BTN_ID_19                                     OBJ_ID_19

/* Button states */
#define BTN_STATE_RELEASED                            (0<<0)
#define BTN_STATE_PRESSED                             (1<<0)
#define BTN_STATE_ALWAYS_REDRAW                       (1<<1)

/* Button style */
#define BTN_STYLE_2D                                  (0<<0)
#define BTN_STYLE_3D                                  (1<<0)
#define BTN_STYLE_TOGGLE_COLORS                       (1<<1)
#define BTN_STYLE_USE_ALTERNATE_COLORS                (1<<2)

/* Button events */
#define BTN_EVENT_CLICKED                             OBJ_EVENT_CLICKED

/* -------------------------------------------------------------------------------- */
/* -- TEXTBOX OBJECT                                                             -- */
/* -------------------------------------------------------------------------------- */
/* Textbox structure */
typedef struct
{
   char* str;
   const UG_FONT* font;
   UG_U8 style;
   UG_COLOR fc;
   UG_COLOR bc;
   UG_U8 align;
   UG_S8 h_space;
   UG_S8 v_space;
} UG_TEXTBOX;

/* Default textbox IDs */
#define TXB_ID_0                                      OBJ_ID_0
#define TXB_ID_1                                      OBJ_ID_1
#define TXB_ID_2                                      OBJ_ID_2
#define TXB_ID_3                                      OBJ_ID_3
#define TXB_ID_4                                      OBJ_ID_4
#define TXB_ID_5                                      OBJ_ID_5
#define TXB_ID_6                                      OBJ_ID_6
#define TXB_ID_7                                      OBJ_ID_7
#define TXB_ID_8                                      OBJ_ID_8
#define TXB_ID_9                                      OBJ_ID_9
#define TXB_ID_10                                     OBJ_ID_10
#define TXB_ID_11                                     OBJ_ID_11
#define TXB_ID_12                                     OBJ_ID_12
#define TXB_ID_13                                     OBJ_ID_13
#define TXB_ID_14                                     OBJ_ID_14
#define TXB_ID_15                                     OBJ_ID_15
#define TXB_ID_16                                     OBJ_ID_16
#define TXB_ID_17                                     OBJ_ID_17
#define TXB_ID_18                                     OBJ_ID_18
#define TXB_ID_19                                     OBJ_ID_19

/* -------------------------------------------------------------------------------- */
/* -- IMAGE OBJECT                                                               -- */
/* -------------------------------------------------------------------------------- */
/* Image structure */
typedef struct
{
   void* img;
   UG_U8 type;
} UG_IMAGE;

/* Default image IDs */
#define IMG_ID_0                                      OBJ_ID_0
#define IMG_ID_1                                      OBJ_ID_1
#define IMG_ID_2                                      OBJ_ID_2
#define IMG_ID_3                                      OBJ_ID_3
#define IMG_ID_4                                      OBJ_ID_4
#define IMG_ID_5                                      OBJ_ID_5
#define IMG_ID_6                                      OBJ_ID_6
#define IMG_ID_7                                      OBJ_ID_7
#define IMG_ID_8                                      OBJ_ID_8
#define IMG_ID_9                                      OBJ_ID_9
#define IMG_ID_10                                     OBJ_ID_10
#define IMG_ID_11                                     OBJ_ID_11
#define IMG_ID_12                                     OBJ_ID_12
#define IMG_ID_13                                     OBJ_ID_13
#define IMG_ID_14                                     OBJ_ID_14
#define IMG_ID_15                                     OBJ_ID_15
#define IMG_ID_16                                     OBJ_ID_16
#define IMG_ID_17                                     OBJ_ID_17
#define IMG_ID_18                                     OBJ_ID_18
#define IMG_ID_19                                     OBJ_ID_19

/* Image types */
#define IMG_TYPE_BMP                                  (1<<0)

/* -------------------------------------------------------------------------------- */
/* -- µGUI DRIVER                                                                -- */
/* -------------------------------------------------------------------------------- */
typedef struct
{
  void* driver;
  UG_U8 state;
} UG_DRIVER;

#define DRIVER_REGISTERED                             (1<<0)
#define DRIVER_ENABLED                                (1<<1)

/* Supported drivers */
#define NUMBER_OF_DRIVERS                             2
#define DRIVER_DRAW_LINE                              0
#define DRIVER_FILL_FRAME                             1

/* -------------------------------------------------------------------------------- */
/* -- µGUI CORE STRUCTURE                                                        -- */
/* -------------------------------------------------------------------------------- */
typedef struct
{
   void (*pset)(UG_S16,UG_S16,UG_COLOR);
   UG_S16 x_dim;
   UG_S16 y_dim;
   UG_TOUCH touch;
   UG_WINDOW* next_window;
   UG_WINDOW* active_window;
   UG_WINDOW* last_window;
   struct
   {
      UG_S16 x_pos;
      UG_S16 y_pos;
      UG_S16 x_start;
      UG_S16 y_start;
      UG_S16 x_end;
      UG_S16 y_end;
      UG_COLOR fore_color;
      UG_COLOR back_color;
   } console;
   struct
   {
      unsigned char* p;
      uint8_t* LUT;
      UG_S16 char_width;
      UG_S16 char_height;
      UG_S8 char_h_space;
      UG_S8 char_v_space;
   } font;
   UG_COLOR fore_color;
   UG_COLOR back_color;
   UG_COLOR desktop_color;
   UG_U8 state;
   UG_DRIVER driver[NUMBER_OF_DRIVERS];
} UG_GUI;

#define UG_SATUS_WAIT_FOR_UPDATE                      (1<<0)

/* -------------------------------------------------------------------------------- */
/* -- µGUI COLORS                                                                -- */
/* -- Source: http://www.rapidtables.com/web/color/RGB_Color.htm                 -- */
/* -------------------------------------------------------------------------------- */

/* 16-bit per pixel color definitions */
#define  C_MAROON                     0x8000
#define  C_DARK_RED                   0x8800
#define  C_BROWN                      0xA145
#define  C_FIREBRICK                  0xB104
#define  C_CRIMSON                    0xD8A7
#define  C_RED                        0xF800
#define  C_TOMATO                     0xFB08
#define  C_CORAL                      0xFBEA
#define  C_INDIAN_RED                 0xCAEB
#define  C_LIGHT_CORAL                0xF410
#define  C_DARK_SALMON                0xECAF
#define  C_SALMON                     0xFC0E
#define  C_LIGHT_SALMON               0xFD0F
#define  C_ORANGE_RED                 0xFA20
#define  C_DARK_ORANGE                0xFC60
#define  C_ORANGE                     0xFD20
#define  C_GOLD                       0xFEA0
#define  C_DARK_GOLDEN_ROD            0xBC21
#define  C_GOLDEN_ROD                 0xDD24
#define  C_PALE_GOLDEN_ROD            0xEF55
#define  C_DARK_KHAKI                 0xBDAD
#define  C_KHAKI                      0xF731
#define  C_OLIVE                      0x8400
#define  C_YELLOW                     0xFFE0
#define  C_YELLOW_GREEN               0x9E66
#define  C_DARK_OLIVE_GREEN           0x5345
#define  C_OLIVE_DRAB                 0x6C64
#define  C_LAWN_GREEN                 0x7FE0
#define  C_CHART_REUSE                0x7FE0
#define  C_GREEN_YELLOW               0xAFE5
#define  C_DARK_GREEN                 0x0320
#define  C_GREEN                      0x07E0
#define  C_FOREST_GREEN               0x2444
#define  C_LIME                       0x07E0
#define  C_LIME_GREEN                 0x3666
#define  C_LIGHT_GREEN                0x9772
#define  C_PALE_GREEN                 0x9FD3
#define  C_DARK_SEA_GREEN             0x8DF1
#define  C_MEDIUM_SPRING_GREEN        0x07D3
#define  C_SPRING_GREEN               0x07EF
#define  C_SEA_GREEN                  0x2C4A
#define  C_MEDIUM_AQUA_MARINE         0x6675
#define  C_MEDIUM_SEA_GREEN           0x3D8E
#define  C_LIGHT_SEA_GREEN            0x2595
#define  C_DARK_SLATE_GRAY            0x2A69
#define  C_TEAL                       0x0410
#define  C_DARK_CYAN                  0x0451
#define  C_AQUA                       0x07FF
#define  C_CYAN                       0x07FF
#define  C_LIGHT_CYAN                 0xE7FF
#define  C_DARK_TURQUOISE             0x067A
#define  C_TURQUOISE                  0x471A
#define  C_MEDIUM_TURQUOISE           0x4E99
#define  C_PALE_TURQUOISE             0xAF7D
#define  C_AQUA_MARINE                0x7FFA
#define  C_POWDER_BLUE                0xB71C
#define  C_CADET_BLUE                 0x5CF4
#define  C_STEEL_BLUE                 0x4416
#define  C_CORN_FLOWER_BLUE           0x64BD
#define  C_DEEP_SKY_BLUE              0x05FF
#define  C_DODGER_BLUE                0x1C9F
#define  C_LIGHT_BLUE                 0xAEDC
#define  C_SKY_BLUE                   0x867D
#define  C_LIGHT_SKY_BLUE             0x867F
#define  C_MIDNIGHT_BLUE              0x18CE
#define  C_NAVY                       0x0010
#define  C_DARK_BLUE                  0x0011
#define  C_MEDIUM_BLUE                0x0019
#define  C_BLUE                       0x001F
#define  C_ROYAL_BLUE                 0x435C
#define  C_BLUE_VIOLET                0x895C
#define  C_INDIGO                     0x4810
#define  C_DARK_SLATE_BLUE            0x49F1
#define  C_SLATE_BLUE                 0x6AD9
#define  C_MEDIUM_SLATE_BLUE          0x7B5D
#define  C_MEDIUM_PURPLE              0x939B
#define  C_DARK_MAGENTA               0x8811
#define  C_DARK_VIOLET                0x901A
#define  C_DARK_ORCHID                0x9999
#define  C_MEDIUM_ORCHID              0xBABA
#define  C_PURPLE                     0x8010
#define  C_THISTLE                    0xDDFB
#define  C_PLUM                       0xDD1B
#define  C_VIOLET                     0xEC1D
#define  C_MAGENTA                    0xF81F
#define  C_ORCHID                     0xDB9A
#define  C_MEDIUM_VIOLET_RED          0xC0B0
#define  C_PALE_VIOLET_RED            0xDB92
#define  C_DEEP_PINK                  0xF8B2
#define  C_HOT_PINK                   0xFB56
#define  C_LIGHT_PINK                 0xFDB8
#define  C_PINK                       0xFE19
#define  C_ANTIQUE_WHITE              0xFF5A
#define  C_BEIGE                      0xF7BB
#define  C_BISQUE                     0xFF38
#define  C_BLANCHED_ALMOND            0xFF59
#define  C_WHEAT                      0xF6F6
#define  C_CORN_SILK                  0xFFDB
#define  C_LEMON_CHIFFON              0xFFD9
#define  C_LIGHT_GOLDEN_ROD_YELLOW    0xFFDA
#define  C_LIGHT_YELLOW               0xFFFC
#define  C_SADDLE_BROWN               0x8A22
#define  C_SIENNA                     0xA285
#define  C_CHOCOLATE                  0xD343
#define  C_PERU                       0xCC27
#define  C_SANDY_BROWN                0xF52C
#define  C_BURLY_WOOD                 0xDDD0
#define  C_TAN                        0xD5B1
#define  C_ROSY_BROWN                 0xBC71
#define  C_MOCCASIN                   0xFF36
#define  C_NAVAJO_WHITE               0xFEF5
#define  C_PEACH_PUFF                 0xFED7
#define  C_MISTY_ROSE                 0xFF3C
#define  C_LAVENDER_BLUSH             0xFF9E
#define  C_LINEN                      0xFF9C
#define  C_OLD_LACE                   0xFFBC
#define  C_PAPAYA_WHIP                0xFF7A
#define  C_SEA_SHELL                  0xFFBD
#define  C_MINT_CREAM                 0xF7FF
#define  C_SLATE_GRAY                 0x7412
#define  C_LIGHT_SLATE_GRAY           0x7453
#define  C_LIGHT_STEEL_BLUE           0xB63B
#define  C_LAVENDER                   0xE73F
#define  C_FLORAL_WHITE               0xFFDE
#define  C_ALICE_BLUE                 0xF7DF
#define  C_GHOST_WHITE                0xFFDF
#define  C_HONEYDEW                   0xF7FE
#define  C_IVORY                      0xFFFE
#define  C_AZURE                      0xF7FF
#define  C_SNOW                       0xFFDF
#define  C_BLACK                      0x0000
#define  C_DIM_GRAY                   0x6B4D
#define  C_GRAY                       0x8410
#define  C_DARK_GRAY                  0xAD55
#define  C_SILVER                     0xC618
#define  C_LIGHT_GRAY                 0xD69A
#define  C_GAINSBORO                  0xDEFB
#define  C_WHITE_SMOKE                0xF7BE
#define  C_WHITE                      0xFFFF

/* -------------------------------------------------------------------------------- */
/* -- PROTOTYPES                                                                 -- */
/* -------------------------------------------------------------------------------- */
/* Classic functions */
UG_S16 UG_Init( UG_GUI* g, void (*p)(UG_S16,UG_S16,UG_COLOR), UG_S16 x, UG_S16 y );
UG_S16 UG_SelectGUI( UG_GUI* g );
void UG_FontSelect( const UG_FONT* font );
void UG_FillScreen( UG_COLOR c );
void UG_FillFrame( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c );
void UG_FillRoundFrame( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_S16 r, UG_COLOR c );
void UG_DrawMesh( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c );
void UG_DrawFrame( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c );
void UG_DrawRoundFrame( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_S16 r, UG_COLOR c );
void UG_DrawPixel( UG_S16 x0, UG_S16 y0, UG_COLOR c );
void UG_DrawCircle( UG_S16 x0, UG_S16 y0, UG_S16 r, UG_COLOR c );
void UG_FillCircle( UG_S16 x0, UG_S16 y0, UG_S16 r, UG_COLOR c );
void UG_DrawArc( UG_S16 x0, UG_S16 y0, UG_S16 r, UG_U8 s, UG_COLOR c );
void UG_DrawLine( UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c );
void UG_PutString( UG_S16 x, UG_S16 y, char* str );
void UG_PutChar( char chr, UG_S16 x, UG_S16 y, UG_COLOR fc, UG_COLOR bc );
void UG_ConsolePutString( char* str );
void UG_ConsoleSetArea( UG_S16 xs, UG_S16 ys, UG_S16 xe, UG_S16 ye );
void UG_ConsoleSetForecolor( UG_COLOR c );
void UG_ConsoleSetBackcolor( UG_COLOR c );
void UG_SetForecolor( UG_COLOR c );
void UG_SetBackcolor( UG_COLOR c );
UG_S16 UG_GetXDim( void );
UG_S16 UG_GetYDim( void );
void UG_FontSetHSpace( UG_U16 s );
void UG_FontSetVSpace( UG_U16 s );

/* Miscellaneous functions */
void UG_WaitForUpdate( void );
void UG_Update( void );
void UG_DrawBMP( UG_S16 xp, UG_S16 yp, const UG_BMP * bmp );
void UG_TouchUpdate( UG_S16 xp, UG_S16 yp, UG_U8 state );

/* Driver functions */
void UG_DriverRegister( UG_U8 type, void* driver );
void UG_DriverEnable( UG_U8 type );
void UG_DriverDisable( UG_U8 type );

/* Window functions */
UG_RESULT UG_WindowCreate( UG_WINDOW* wnd, UG_OBJECT* objlst, UG_U8 objcnt, void (*cb)( UG_MESSAGE* ) );
UG_RESULT UG_WindowDelete( UG_WINDOW* wnd );
UG_RESULT UG_WindowShow( UG_WINDOW* wnd );
UG_RESULT UG_WindowHide( UG_WINDOW* wnd );
UG_RESULT UG_WindowResize( UG_WINDOW* wnd, UG_S16 xs, UG_S16 ys, UG_S16 xe, UG_S16 ye );
UG_RESULT UG_WindowAlert( UG_WINDOW* wnd );
UG_RESULT UG_WindowSetForeColor( UG_WINDOW* wnd, UG_COLOR fc );
UG_RESULT UG_WindowSetBackColor( UG_WINDOW* wnd, UG_COLOR bc );
UG_RESULT UG_WindowSetTitleTextColor( UG_WINDOW* wnd, UG_COLOR c );
UG_RESULT UG_WindowSetTitleColor( UG_WINDOW* wnd, UG_COLOR c );
UG_RESULT UG_WindowSetTitleInactiveTextColor( UG_WINDOW* wnd, UG_COLOR c );
UG_RESULT UG_WindowSetTitleInactiveColor( UG_WINDOW* wnd, UG_COLOR c );
UG_RESULT UG_WindowSetTitleText( UG_WINDOW* wnd, char* str );
UG_RESULT UG_WindowSetTitleTextFont( UG_WINDOW* wnd, const UG_FONT* font );
UG_RESULT UG_WindowSetTitleTextHSpace( UG_WINDOW* wnd, UG_S8 hs );
UG_RESULT UG_WindowSetTitleTextVSpace( UG_WINDOW* wnd, UG_S8 vs );
UG_RESULT UG_WindowSetTitleTextAlignment( UG_WINDOW* wnd, UG_U8 align );
UG_RESULT UG_WindowSetTitleHeight( UG_WINDOW* wnd, UG_U8 height );
UG_RESULT UG_WindowSetXStart( UG_WINDOW* wnd, UG_S16 xs );
UG_RESULT UG_WindowSetYStart( UG_WINDOW* wnd, UG_S16 ys );
UG_RESULT UG_WindowSetXEnd( UG_WINDOW* wnd, UG_S16 xe );
UG_RESULT UG_WindowSetYEnd( UG_WINDOW* wnd, UG_S16 ye );
UG_RESULT UG_WindowSetStyle( UG_WINDOW* wnd, UG_U8 style );
UG_COLOR UG_WindowGetForeColor( UG_WINDOW* wnd );
UG_COLOR UG_WindowGetBackColor( UG_WINDOW* wnd );
UG_COLOR UG_WindowGetTitleTextColor( UG_WINDOW* wnd );
UG_COLOR UG_WindowGetTitleColor( UG_WINDOW* wnd );
UG_COLOR UG_WindowGetTitleInactiveTextColor( UG_WINDOW* wnd );
UG_COLOR UG_WindowGetTitleInactiveColor( UG_WINDOW* wnd );
char* UG_WindowGetTitleText( UG_WINDOW* wnd );
UG_FONT* UG_WindowGetTitleTextFont( UG_WINDOW* wnd );
UG_S8 UG_WindowGetTitleTextHSpace( UG_WINDOW* wnd );
UG_S8 UG_WindowGetTitleTextVSpace( UG_WINDOW* wnd );
UG_U8 UG_WindowGetTitleTextAlignment( UG_WINDOW* wnd );
UG_U8 UG_WindowGetTitleHeight( UG_WINDOW* wnd );
UG_S16 UG_WindowGetXStart( UG_WINDOW* wnd );
UG_S16 UG_WindowGetYStart( UG_WINDOW* wnd );
UG_S16 UG_WindowGetXEnd( UG_WINDOW* wnd );
UG_S16 UG_WindowGetYEnd( UG_WINDOW* wnd );
UG_U8 UG_WindowGetStyle( UG_WINDOW* wnd );
UG_RESULT UG_WindowGetArea( UG_WINDOW* wnd, UG_AREA* a );
UG_S16 UG_WindowGetInnerWidth( UG_WINDOW* wnd );
UG_S16 UG_WindowGetOuterWidth( UG_WINDOW* wnd );
UG_S16 UG_WindowGetInnerHeight( UG_WINDOW* wnd );
UG_S16 UG_WindowGetOuterHeight( UG_WINDOW* wnd );

/* Button functions */
UG_RESULT UG_ButtonCreate( UG_WINDOW* wnd, UG_BUTTON* btn, UG_U8 id, UG_S16 xs, UG_S16 ys, UG_S16 xe, UG_S16 ye );
UG_RESULT UG_ButtonDelete( UG_WINDOW* wnd, UG_U8 id );
UG_RESULT UG_ButtonShow( UG_WINDOW* wnd, UG_U8 id );
UG_RESULT UG_ButtonHide( UG_WINDOW* wnd, UG_U8 id );
UG_RESULT UG_ButtonSetForeColor( UG_WINDOW* wnd, UG_U8 id, UG_COLOR fc );
UG_RESULT UG_ButtonSetBackColor( UG_WINDOW* wnd, UG_U8 id, UG_COLOR bc );
UG_RESULT UG_ButtonSetAlternateForeColor( UG_WINDOW* wnd, UG_U8 id, UG_COLOR afc );
UG_RESULT UG_ButtonSetAlternateBackColor( UG_WINDOW* wnd, UG_U8 id, UG_COLOR abc );
UG_RESULT UG_ButtonSetText( UG_WINDOW* wnd, UG_U8 id, char* str );
UG_RESULT UG_ButtonSetFont( UG_WINDOW* wnd, UG_U8 id, const UG_FONT* font );
UG_RESULT UG_ButtonSetStyle( UG_WINDOW* wnd, UG_U8 id, UG_U8 style );
UG_COLOR UG_ButtonGetForeColor( UG_WINDOW* wnd, UG_U8 id );
UG_COLOR UG_ButtonGetBackColor( UG_WINDOW* wnd, UG_U8 id );
UG_COLOR UG_ButtonGetAlternateForeColor( UG_WINDOW* wnd, UG_U8 id );
UG_COLOR UG_ButtonGetAlternateBackColor( UG_WINDOW* wnd, UG_U8 id );
char* UG_ButtonGetText( UG_WINDOW* wnd, UG_U8 id );
UG_FONT* UG_ButtonGetFont( UG_WINDOW* wnd, UG_U8 id );
UG_U8 UG_ButtonGetStyle( UG_WINDOW* wnd, UG_U8 id );

/* Textbox functions */
UG_RESULT UG_TextboxCreate( UG_WINDOW* wnd, UG_TEXTBOX* txb, UG_U8 id, UG_S16 xs, UG_S16 ys, UG_S16 xe, UG_S16 ye );
UG_RESULT UG_TextboxDelete( UG_WINDOW* wnd, UG_U8 id );
UG_RESULT UG_TextboxShow( UG_WINDOW* wnd, UG_U8 id );
UG_RESULT UG_TextboxHide( UG_WINDOW* wnd, UG_U8 id );
UG_RESULT UG_TextboxSetForeColor( UG_WINDOW* wnd, UG_U8 id, UG_COLOR fc );
UG_RESULT UG_TextboxSetBackColor( UG_WINDOW* wnd, UG_U8 id, UG_COLOR bc );
UG_RESULT UG_TextboxSetText( UG_WINDOW* wnd, UG_U8 id, char* str );
UG_RESULT UG_TextboxSetFont( UG_WINDOW* wnd, UG_U8 id, const UG_FONT* font );
UG_RESULT UG_TextboxSetHSpace( UG_WINDOW* wnd, UG_U8 id, UG_S8 hs );
UG_RESULT UG_TextboxSetVSpace( UG_WINDOW* wnd, UG_U8 id, UG_S8 vs );
UG_RESULT UG_TextboxSetAlignment( UG_WINDOW* wnd, UG_U8 id, UG_U8 align );
UG_COLOR UG_TextboxGetForeColor( UG_WINDOW* wnd, UG_U8 id );
UG_COLOR UG_TextboxGetBackColor( UG_WINDOW* wnd, UG_U8 id );
char* UG_TextboxGetText( UG_WINDOW* wnd, UG_U8 id );
UG_FONT* UG_TextboxGetFont( UG_WINDOW* wnd, UG_U8 id );
UG_S8 UG_TextboxGetHSpace( UG_WINDOW* wnd, UG_U8 id );
UG_S8 UG_TextboxGetVSpace( UG_WINDOW* wnd, UG_U8 id );
UG_U8 UG_TextboxGetAlignment( UG_WINDOW* wnd, UG_U8 id );

/* Image functions */
UG_RESULT UG_ImageCreate( UG_WINDOW* wnd, UG_IMAGE* img, UG_U8 id, UG_S16 xs, UG_S16 ys, UG_S16 xe, UG_S16 ye );
UG_RESULT UG_ImageDelete( UG_WINDOW* wnd, UG_U8 id );
UG_RESULT UG_ImageShow( UG_WINDOW* wnd, UG_U8 id );
UG_RESULT UG_ImageHide( UG_WINDOW* wnd, UG_U8 id );
UG_RESULT UG_ImageSetBMP( UG_WINDOW* wnd, UG_U8 id, const UG_BMP* bmp );



#endif
