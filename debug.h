#ifndef DEBUG_H_
#define DEBUG_H_

enum {
	MSG_DEBUG, MSG_INFO, MSG_WARRING, MSG_ERROR
};

//#define anbin_printf (args...) do {} while (0)
//#define anbin_debug_open_file (p) do {} while (0)
//#define anbin_printf (int level, const char *fmt) do {} while (0)
//#define anbin_debug_open_file (const char *path) do {} while (0)

<<<<<<< HEAD
void anbin_printf (int level, const char *fmt, ...);
=======
void anbin_printf (int level, const char *fmt);
>>>>>>> 9e5021e7d20ffe6d69a78d4e920dcb07be5b1b84
int anbin_debug_open_file (const char *path);



#endif
