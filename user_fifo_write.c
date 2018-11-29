#include <stdio.h>
#include <stdlib.h>
#include "user_fifo.h"
#include "unix_fifo_ops.h"
#include "slog.h"

unixFifoOps_t *user_fifo_write_init (const char *path) {
	unixFifoOps_t* ptr = unix_fifo_ops_create (path, 0);
	if (!ptr) {
		err ("ptr create failed!");
		return NULL;
	}
	int ret = fd_change_flag (ptr->fd, O_NONBLOCK);
	if (ret < 0) {
		err ("fd_change_flag failed!");
		return NULL;
	}
	return ptr;
}

int user_fifo_write_str (unixFifoOps_t* ptr, char *contex) {
	if (!ptr) {
		err ("ptr is null");
		return -1;
	}
	size_t size = strlen (contex);
	int ret = unix_fifo_ops_write (ptr, contex, size);
	if (ret < 0) {
		ret = unix_fifo_ops_init (ptr);
		if (ret < 0)
			return -2;
		ret = unix_fifo_ops_write (ptr, contex, size);
		if (ret < 0)
			return -3;
	}
	return 0;
}

int user_fifo_write_fmt (unixFifoOps_t* ptr, const char *fmt, ...) {
	char buf[1024] = FMT_PREFIX;
	char *contex = buf + FMT_PREFIX_LEN;
	size_t  availableSize = sizeof (buf) - FMT_PREFIX_LEN - FMT_SUBFFIX_LEN -1;
	va_list args;
	va_start (args, fmt);
	ssize_t ret = vsnprintf (contex, availableSize, fmt, args);
	if (ret <= 0) {
		err ("vsnprintf err!");
		return -1;
	}
	if (ret >= availableSize) {
		err ("vnsprintf buf isn't enough!");
		return -2;
	}
	va_end (args);
	strcat (buf, FMT_PREFIX);
	ssize_t wRet = user_fifo_write_str (ptr, buf);
	if (wRet < ret)
		return -3;
	return 0;
}

int user_fifo_write_fmt_len (unixFifoOps_t* ptr, siez_t len, const char *fmt, ...) {
	char buf[1024] = FMT_PREFIX;
	char *contex = buf + FMT_PREFIX_LEN;
	size_t  availableSize = sizeof (buf) - FMT_PREFIX_LEN - FMT_SUBFFIX_LEN -1;
	va_list args;
	va_start (args, fmt);
	ssize_t ret = vsnprintf (contex, availableSize, fmt, args);	//??
	if (ret <= 0) {
		err ("vsnprintf err!");
		return -1;
	}
	if (ret >= availableSize) {
		err ("vnsprintf buf isn't enough!");
		return -2;
	}
	va_end (args);
	strcat (buf, FMT_PREFIX);
	ssize_t wRet = user_fifo_write_str (ptr, buf);
	if (wRet < ret)
		return -3;
	return 0;
}
