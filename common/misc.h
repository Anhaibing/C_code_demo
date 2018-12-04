#ifndef __MISC_H__
#define __MISC_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <ctype.h>
#include <syscall.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/types.h>

#define ANBIN_MIN(x, y) ((x)<(y)?(x):(y))
#define FREE(x) if(x){free(x);x = NULL;}
#define ADD_HANDLE_ITEM(name, args) {#name, name##_handle, args},

char** argl_to_argv (char arg1[], int *pArgc);


#endif
