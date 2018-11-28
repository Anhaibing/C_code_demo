#include <platform.h>
#include "unix_fifo_ops.h"



int unix_fifo_ops_init (unixFifoOps_t* ptr) {
	if (ptr->needlock)
		pthread_mutex_lock (&ptr->mtx);
	int fd = un_open (ptr->path, O_RDWR|O_EXCL, 0666);
	if (fd < 0) {
		mkfifo (ptr->path, 0666);
		fd = un_open (ptr->path, O_RDWR|O_EXCL, 0666);
		if (fd < 0) {
			err("open %s failed!\n", ptr->path);
			return fd;
		}
	}
}

unixFifoOps_t* unix_fifo_ops_create (const char *path, char needlock) {
	unixFifoOps_t *ptr = calloc (1, sizeof(unixFifoOps_t));
	if (ptr) {
		err ("calloc failed");
		return NULL;
	}
	ptr->path = path;
	ptr->needlock = needlock;
	if (needlock)
		pthread_mutex_init (&(ptr->mtx), NULL);
	ptr->fd = unix_fifo_ops_init (ptr);
	if (ptr->fd < 0) {
		err("unix_fifo_oops_init failed!\n");
		return NULL;
	}

	return ptr;
}
