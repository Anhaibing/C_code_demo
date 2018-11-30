#ifndef __FD_OP_H__
#define __FD_OP_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include "misc.h"
#include "slog.h"

#define un_open(path,flags,mode) ({\
	int fd=0;\
	fd=open(path,flags,mode);\
	if(-1==fd){\
		show_errno(0,"open!");\
	}\
	fd;\
})
#define un_read(fd,buf,size) ({\
	ssize_t ret=0,count=0;\
	for(;;){\
		ret=read(fd,buf+count,size-count);\
		if(ret>0)count+=ret;\
		if(count==size){\
			break;\
		}\
		if(errno==EINTR){\
			show_errno(0,"read");\
			continue;\
		}\
		if(ret<0){\
			show_errno(0,"read");\
		}\	
		break;\
	}\
	count;\
})

#define un_write(fd,buf,size) ({\
	ssize_t ret=0,count=0;\
	for(;;){\
		ret=write(fd,buf+count,size-count);\
		if(ret>0)count+=ret;\
		if(count==size){\
			break;\
		}\
		if(errno==EINTR){\
			show_errno(0,"write");\
			continue;\
		}\
		if(ret<0){\
			show_errno(0,"read");\
		}\
		break;\
	}\
	count;\
})

#define un_lseek(fd,offset,whence) ({\
	ssize_t ret=0;\
	ret=lseek(fd,offset,whence);\
	if(-1==ret){\
		show_errno(0,"lseek");\
	}\
	ret=-1==ret?-1:0;\
})
#define un_close(fd) ({\
	int ret=0;\
	ret=close(fd);\
	if(-1==ret){\
		show_errno(0,"close");\
	}\
	ret=-1==ret?-1:0;\
})
//经测试ulink 可以直接删除/tmp/tt1 并不管其他的进程是否打卡此文件
#define un_unlink(path) ({\
	int ret=0;\
	ret=unlink(path);\
	if(-1==ret){\
		show_errno(0,"unlink");\
	}\
	ret=-1==ret?-1:0;\
})
#define un_fstat(p_stat,fd) ({\
	int ret=0;\
	ret=fstat(fd,p_stat);\
	if(-1==ret){\
		show_errno(0,"fstat");\
	}\
	ret;\
})

int fd_change_flag (int fd, int flag);

#endif
