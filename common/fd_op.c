#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "fd_op.h"

int fd_change_flag(int fd, int flag) {
	int flags = fcntl (fd, F_GETFL, 0);
	if (flags < 0) {
		show_errno(0, "fcntl F_GETFL failed!");
		return -1;
	}
	int ret = fcntl (fd, F_SETFL, flags|flag);
	if (ret < 0) {
		show_errno(0, "fcntl F_SETFL failed!");
		return -2;
	}
	return 0;
}