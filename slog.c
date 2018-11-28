#include "slog.h"

log_ctrl_t logCtrlArray[MAX_TYPE] = {
	[_ERR] = {"ERR"		,Hred	},
	[_WAR] = {"WAR"		,Hyellow},
	[_INF] = {"INF"		,Hgreen	},
	[_DBG] = {"DBG"		,Hblue	},
	[_TRC] = {"TRC"		,Hpurple},
};

static FILE *fp = NULL;

char log_ctrl_set[MAX_TYPE+1] = "111";

pthread_mutex_t line_lock = PTHREAD_MUTEX_INITIALIZER;

void get_time_ms(char *ts, int size) {
	struct timeval tv={0};
	if (gettimeofday(&tv, NULL) < 0)
		return;
}

int log_init(char *ctrl, char *path) {
	if (ctrl) {
		strncpy(log_ctrl_set, ctrl, cmp1(sizeof(log_ctrl_set), strlen(ctrl)));
	}
	if (path) {
		pthread_mutex_lock (&line_lock);
		if (!(fp = fopen(path, 'a'))) {
			printf ("fopen %s failed, error = %d\n", path, errno);
			fp = stdout;
		}
		pthread_mutex_unlock(&line_lock);
	}
}

inline void slog(log_type_t n,
		char lock,
		char *log_ctrl_set,
		const char *ts,
		const char *file,
		const int line,
		const char *fmt,
		...) {
	if ('1' == log_ctrl_set[n]) {
		if (lock)
			pthread_mutex_lock(&line_lock);
		if (!fp)
			fp = stdout;
		va_list args;
		fprintf (fp, "[%s%s%s\033[0m %s:%d]:", ts, logCtrlArray[n].color, logCtrlArray[n].name, get_last_name(file), line);
		va_start(args, fmt);
		vfprintf(fp, fmt, args);
		va_end(args);
		fprintf(fp, "\n");
		if (lock)
			pthread_mutex_unlock(&line_lock);
	}
}
