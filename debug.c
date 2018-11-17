#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "debug.h"

static FILE *out_file = NULL;

int MSG_DEBUG_LEVEL = MSG_INFO;

<<<<<<< HEAD
void anbin_printf (int level, const char *fmt, ...) {
=======
void anbin_printf (int level, const char *fmt) {
>>>>>>> 9e5021e7d20ffe6d69a78d4e920dcb07be5b1b84
	va_list ap;
	va_start (ap, fmt);
	if (level > MSG_DEBUG_LEVEL) {
		if (out_file) {
			vfprintf (out_file, fmt, ap);
			fprintf (out_file, "\n");
		} else {
			vprintf (fmt, ap);
			printf ("\n");
		}
	}
	va_end (ap);
}

int anbin_debug_open_file (const char *path) {
	if (!path) return 0;
	out_file = fopen (path, 'a');
	if (out_file == NULL) {
		anbin_printf (MSG_ERROR, "_debug_open_file: failed open"
				"output file, use standard output");
		return -1;
	}

	return 0;

}
