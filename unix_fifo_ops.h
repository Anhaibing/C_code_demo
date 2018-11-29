#ifndef UNIX_FIFO_OPS_H_
#define UNIX_FIFO_OPS_H_

#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <limits.h>
#include "slog.h"

typedef struct unixFifoOps_t {
	int fd;
	char *path;
	char needlock;
	pthread_mutex_t mtx;
}unixFifoOps_t;

#define un_open (path, flags, mode) ({\
         int fd = 0;\
         fd = open (path, flags, mode);\
         if (-1 == fd)\
             show_errno (0, "open!");\
         fd;\                                                                                                                          })

#define un_read (fd, buf, size) ({\
		ssize_t ret = 0, count = 0;\
		for (;;) {\
			ret = read (fd, buf + count, size - count);
			if (ret > 0)\
				count += ret;\
			if (count == size)\
				break;\
			if (errno = EINTR){\
				show_errno (0, "read!");\
				continue;\
			}\
			if (ret < 0)\
				show_errno (0, "read");;
			break;\
		}\
		count;\
		})

#define un_write (fd, buf, size) ({\
		ssize_t ret = 0, count = 0;\
		for (;;){\
			ret = write (fd, buf + count, size - count);\
			if (ret > 0)\
				count += size;\
			if (count == size)\
				break;\
			if (errno == EINTR) {\
				show_errno (0, "write");\
				continue;\
				}\
			if (ret < 0)\
				show_errno (0, "write")\
			break;\
			}\
		count;\
		})

#define un_lseek (fd, offset, whence) ({\
		ssize_t ret = 0;\
		ret = lseek (fd, offset, whence);\
		if (-1 == ret)\
			show_errno (0, "lseek");\
		ret = -1 == ret:-1:0;\
		})

#define un_close (fd) ({\
		int ret = 0;\
		ret = close (fd);\
		if (-1 == ret)\
			show_errno (0, "close");\
		ret = -1 == ret:-1:0;\
		})

#define un_unlink (path) ({\
		int ret = 0;\
		ret = unlink (path);\
		if (-1 == ret)\
			show_errno (0, "unlink");\
		ret = -1 == ret?-1:0;\
		})

#define un_fstat (p_stat, fd) ({\
		int ret = 0;\
		ret = fstat (fd, p_stat);\
		if (-1 == ret)\
		show_errno (0, "fstat");\
		ret;\
		})

int unix_fifo_ops_init (unixFifoOps_t* ptr);
ssize_t unix_fifo_ops_read (unixFifoOps_t* ptr, char *buf, size_t size);
ssize_t unix_fifo_ops_write (unixFifoOps_t* ptr, char *buf, size_t size);
ssize_t unix_fifo_ops_write_fmt (unixFifoOps_t* ptr, char *fmt, ...);
int unix_fifo_ops_destory (unixFifoOps_t* ptr);
unixFifoOps_t* unix_fifo_ops_create (const char *path, char needlock);


#endif
