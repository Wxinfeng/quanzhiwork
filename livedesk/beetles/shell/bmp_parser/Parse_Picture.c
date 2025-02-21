/*
*************************************************************************************
*                         			eGon
*					        Application Of eGon2.0
*
*				(c) Copyright 2006-2010, All winners Co,Ld.
*							All	Rights Reserved
*
* File Name 	: Parse_Picture.c
*
* Author 		: javen
*
* Description 	: 图片解析
*
* History 		:
*      <author>    		<time>       	<version >    		<desc>
*       javen     	   2010-09-10          1.0            create this file
*
*************************************************************************************
*/

#include  "..\\Esh_shell_private.h"
#include  "Parse_Picture.h"
#include  "bmp.h"

#define spcl_size_align( x, y )         ( ( (x) + (y) - 1 ) & ~( (y) - 1 ) )
#define abs(x) (x) >= 0 ? (x):-(x)
/*
*******************************************************************************
*                     Parse_Pic_BMP_ByBuffer
*
* Description:
*    解析存放在内存中的图片
*
* Parameters:
*    Pic_Buffer     :  input.  存放图片的入口
*    Pic_BufferSize :  input.  缓冲区大小
*    PictureInfo    :  output. 图片解析后的信息
*
* Return value:
*    void
*
* note:
*    void
*
*******************************************************************************
*/
__s32 Parse_Pic_BMP_ByBuffer(void *Pic_Buffer, __u32 Pic_BufferSize, Picture_t *PictureInfo)
{
    bmp_info_head_t *info_head_p = NULL;

    info_head_p = (bmp_info_head_t *)((__u32)Pic_Buffer + sizeof(bmp_file_head_t));

    PictureInfo->BitCount = info_head_p->biBitCount;
    PictureInfo->Width    = info_head_p->biWidth;
    PictureInfo->Height	  = abs(info_head_p->biHeight);
    PictureInfo->RowSize  = spcl_size_align( info_head_p->biWidth * ( info_head_p->biBitCount >> 3 ), 4 );

    PictureInfo->Buffer     = (void *)((__u32)Pic_Buffer + sizeof(bmp_info_head_t) + sizeof(bmp_file_head_t));
    PictureInfo->BufferSize = Pic_BufferSize - (sizeof(bmp_info_head_t) + sizeof(bmp_file_head_t));

    return 0;
}

/*
*******************************************************************************
*                     Parse_Pic_BMP
*
* Description:
*    以路径名来解析图片, 并且把解析处理的图片拷贝到指定的地址，
* 如果指定的地址为NULL, 则可以存放在任何地址。
*
* Parameters:
*    Path           :  input.  图片路径
*    PictureInfo    :  output. 图片解析后的信息
*    Addr			:  input.  存放解析后的图片,
*
* Return value:
*    void
*
* note:
*    void
*
*******************************************************************************
*/
__s32 Parse_Pic_BMP_ByPath(char *Path, Picture_t *PictureInfo, __u32 Addr)
{
    HBMP_i_t hbmp_buf;
    HBMP  hbmp = NULL;

    eLIBs_memset(&hbmp_buf, 0, sizeof(HBMP_i_t));
    hbmp = open_bmp(Path, &hbmp_buf);
    if(hbmp == NULL)
    {
        __wrn("ERR: open_bmp failed\n");
        return -1;
    }

    PictureInfo->BitCount = get_bitcount(hbmp);
    PictureInfo->Width    = get_width(hbmp);
    PictureInfo->Height	  = get_height(hbmp);
    PictureInfo->RowSize  = get_rowsize(hbmp);

    PictureInfo->BufferSize = PictureInfo->RowSize * PictureInfo->Height;
    if(Addr)
    {
        PictureInfo->Buffer = (void *)Addr;
    }
    else
    {
        PictureInfo->Buffer = (void *)esMEMS_Balloc(PictureInfo->BufferSize);
    }
    if(PictureInfo->Buffer == NULL)
    {
        __wrn("ERR: wboot_malloc failed\n");
        goto error;
    }

    eLIBs_memset(PictureInfo->Buffer, 0, PictureInfo->BufferSize);

    get_matrix(hbmp, PictureInfo->Buffer);

    close_bmp(hbmp);
    hbmp = NULL;

    return 0;

error:
    close_bmp(hbmp);

    return -1;
}

