#/*
#*********************************************************************************************************
#*                                                    MELIS
#*                                    the Easy Portable/Player Develop Kits
#*                                               makefile Module
#*
#*                                    (c) Copyright 2006-2010, kevin.z China
#*                                             All Rights Reserved
#*
#* File    : makefile
#* By      : kevin.z
#* Version : v1.0
#* Date    : 2010-9-3 9:39
#* Descript:
#* Update  : date                auther      ver     notes
#*********************************************************************************************************
#*/



#生成输出目标文件
all:
	make -C eLibs
	make -C eMod
	make -C livedesk	

#生产烧录文件
image:
	cd ./workspace/suniv/beetles && ./image.bat
	
    
# 删除生成的中间文件
clean:
	make -C eLibs       clean
	make -C eMod       clean
	make -C livedesk         clean
