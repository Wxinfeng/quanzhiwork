/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUI_CursorCrossS.C
Purpose     : Defines the cross cursor, small
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "gui_core_kernel_private.h"

GUI_CONST_STORAGE GUI_BITMAP GUI_BitmapCrossS =
{
    11,                   /* XSize */
    11,                   /* YSize */
    3,                    /* BytesPerLine */
    2,                    /* BitsPerPixel */
    GUI_Pixels_CrossS,    /* Pointer to picture data (indices) */
    &GUI_CursorPal       /* Pointer to palette */
};


GUI_CONST_STORAGE GUI_CURSOR GUI_CursorCrossS =
{
    &GUI_BitmapCrossS, 5, 5
};


/*************************** End of file ****************************/

