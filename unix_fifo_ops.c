#include "unix_fifo_ops.h"
#include "fd_op.h"


int unix_fifo_ops_init (unixFifoOps_t* ptr) {
	if (ptr->needlock)
		pthread_mutex_lock (&ptr->mtx);
	int fd = un_open (ptr->path, O_RDWR|O_EXCL, 0666);
	if (fd < 0) {
		mkfifo (ptr->path, 0666);
		fd = un_open (ptr->path, O_RDWR|O_EXCL, 0666);
		if (fd < 0) {
			//err("open %s failed!\n", ptr->path);
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
		//err("unix_fifo_oops_init failed!\n");
		return NULL;
	}

	return ptr;
}

ssize_t unix_fifo_ops_read (unixFifoOps_t* ptr, char *buf, size_t size) {
	ssize_t ret = un_read (ptr->fd, buf, size);
	if (ret < 0)
		return -1;
	return ret;
}

ssize_t unix_fifo_ops_write (unixFifoOps_t* ptr, char *buf, size_t size) {
	if (ptr->needlock)
		pthread_mutex_lock (&ptr->mtx);
	char *widx = buf;
	size_t remSize = size;
	ssize_t ret = 0;

	for (;remSize < PIPE_BUF;) {
		ret = un_write (ptr->fd, widx, remSize);
		if (ret < 0)
			goto exit;
		remSize -= PIPE_BUF;
		widx += PIPE_BUF;
	}

	ret = un_write (ptr->fd, widx, remSize);
	if (ret < 0)
		goto exit;
exit:
	if (ptr->needlock)
		pthread_mutex_unlock(&ptr->mtx);
	return ret;
}

int unix_fifo_ops_destory (unixFifoOps_t* ptr) {
	if (ptr->needlock)
		pthread_mutex_lock (&ptr->mtx);
	int ret = un_close (ptr->fd);
	pthread_mutex_t* pMtx = &ptr->mtx;
	char needlock = ptr->needlock;
	free(ptr);
	ptr = NULL;
exit:
	if (needlock) {
		pthread_mutex_unlock (pMtx);
		pthread_mutex_destroy (pMtx);
	}
	return ret;
}
