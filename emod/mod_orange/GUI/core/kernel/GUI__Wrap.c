/*
**********************************************************************************************************************
*                                                    ePDK
*                                    the Easy Portable/Player Develop Kits
*                                              eMOD Sub-System
*
*                                   (c) Copyright 2007-2009, Steven.ZGJ.China
*                                             All Rights Reserved
*
* Moudle  : lemon
* File    : GUI__WRAP.c
* Purpose : Implementation of wrap routines
*
* By      : Miracle
* Version : v1.0
* Date    : 2009-2-19 10:58:42
**********************************************************************************************************************
*/

#include "gui_core_kernel_private.h"

/*********************************************************************
*
*       static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _IsLineEnd
*/
static int _IsLineEnd(U16 Char, const char *s)
{
    U16   tmpchar;

    if(!Char || (Char == '\n') || (Char == '\r')) //modified by Derek 2010.12.02.10:07
    {
        return 1;
    }

    return 0;
}

/*********************************************************************
*
*       _GetWordWrap
*/
static int _GetWordWrap(const char GUI_UNI_PTR *s, int xSize)
{
    int xDist = 0, NumChars = 0, WordWrap = 0;
    U16 Char, PrevChar = 0;

    while (1)
    {
        Char = GUI_UC__GetCharCodeInc(&s);   /* Similar to:  *s++ */
        /* Let's first check if the line end is reached. In this case we are done. */
        if (_IsLineEnd(Char, s))
        {
            WordWrap = NumChars;
            break;
        }
        /* If current character is a space, we found a wrap position */
        if ((Char == ' ') && (Char != PrevChar))
        {
            WordWrap = NumChars;
        }
        PrevChar = Char;
        xDist += GUI_GetCharDistX(Char);
        if ((xDist <= xSize) || (NumChars == 0))
        {
            NumChars++;
        }
        else
        {
            break;
        }
    }
    if (!WordWrap)
    {
        WordWrap = NumChars;
    }

    return WordWrap;
}

/*********************************************************************
*
*       _GetCharWrap
*/
static int _GetCharWrap(const char GUI_UNI_PTR *s, int xSize)
{
    int xDist = 0, NumChars = 0;
    U16 Char;

    while ((Char = GUI_UC__GetCharCodeInc(&s)) != 0)
    {
        xDist += GUI_GetCharDistX(Char);
        if ((NumChars && (xDist > xSize)) || (Char == '\n') || (Char == '\r'))
        {
            break;
        }
        NumChars++;
    }

    return NumChars;
}

/*********************************************************************
*
*       _GetNoWrap
*/
static int _GetNoWrap(const char GUI_UNI_PTR *s)
{
    return GUI__GetLineNumChars(s, 0x7FFF);
}

/*********************************************************************
*
*       puplic code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI__WrapGetNumCharsDisp
*
* Returns:
*  Number of characters to display in the line.
*  Trailing spaces and line end character are
*  not counted
*/
int GUI__WrapGetNumCharsDisp(const char GUI_UNI_PTR *pText, int xSize, GUI_WRAPMODE WrapMode)
{
    int r;

    switch (WrapMode)
    {
    case GUI_WRAPMODE_WORD:
        r = _GetWordWrap(pText, xSize);
        break;

    case GUI_WRAPMODE_CHAR:
        r = _GetCharWrap(pText, xSize);
        break;

    default:
        r = _GetNoWrap(pText);
    }
    return r;
}

/*********************************************************************
*
*       GUI__WrapGetNumCharsToNextLine
*/
int GUI__WrapGetNumCharsToNextLine(const char GUI_UNI_PTR *pText, int xSize, GUI_WRAPMODE WrapMode)
{
    int NumChars;
    U16 Char;

    NumChars = GUI__WrapGetNumCharsDisp(pText, xSize, WrapMode);
    pText   += GUI_UC__NumChars2NumBytes(pText, NumChars);
    Char     = GUI_UC__GetCharCodeInc(&pText);
    if (Char == '\n')
    {
        NumChars++;
    }
    else if(Char == '\r')  //modified by Derek 2010.12.02.10:07
    {
        NumChars++;
        Char = GUI_UC__GetCharCodeInc(&pText);

        if(Char == '\n')
        {
            NumChars++;
        }
    }
    else
    {
        if (WrapMode == GUI_WRAPMODE_WORD)
        {
            while (Char == ' ')
            {
                NumChars++;
                Char = GUI_UC__GetCharCodeInc(&pText);
            }
        }
    } //end modified
    return NumChars;
}

/*********************************************************************
*
*       GUI__WrapGetNumBytesToNextLine
*/
int GUI__WrapGetNumBytesToNextLine(const char GUI_UNI_PTR *pText, int xSize, GUI_WRAPMODE WrapMode)
{
    int NumChars, NumBytes;

    NumChars = GUI__WrapGetNumCharsToNextLine(pText, xSize, WrapMode);
    NumBytes = GUI_UC__NumChars2NumBytes(pText, NumChars);

    return NumBytes;
}

/*************************** End of file ****************************/

