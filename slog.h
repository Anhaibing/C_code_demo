#ifndef _SLOH_H_
#define _SLOG_H_ 1
#include "com_log.h"

typedef enum log_type_t {
	MIN_TYPE = -1,
	_RAW,
	_ERR,
	_WAR,
	_INF,
	_DBG,
	_TRC,
	MAX_TYPE
} log_type_t;

typedef struct log_ctrl_t {
	char *name;
	char *color;
} log_ctrl_t;

extern char log_ctrl_set[MAX_TYPE+1];

void get_time_ms(char *ts, int size);

int log_init(char *ctrl, char *path);

void slog (log_type_t type,	//log level
		char lock_en,		//mutex en/dis
		char *log_ctrl_set,	//log en/dis ctrl
		const char *ts,		//time string
		const char *file,	//call function name(__FUNC__)
		const int line,		//call line number(__LINE__)
		const char *fmt,	//output format string
		...);

void raw_log (log_type_t,
		char lock,
		char *log_ctrl_set,
		const char *fmt,
		...);

#define dlog(type, lock, x...)	slog(type, lock, log_ctrl_set, "", __FILE__, __LINE__, x);

#define rlog(type, lock, x...)	raw_log(type, lock, log_ctrl_set, x);

#define tlog(type, x...) ({\
		char ts[16] = "";\
		get_time_ms(ts, sizeof(ts));\
		slog(type, log_ctrl_set, ts, __FILE__, __LINE__, x);\
})

#define show_errno(ret, msg) ({\
		int num = (ret);\
		if (!num) num = errno;\
		err("%s failure, errno:%d[%s]", msg, num, strerror(num));\
})

#define raw(x...)	rlog(_RAW, 1, x);
#define err(x...)	dlog(_ERR, 1, x);
#define war(x...)	dlog(_WAR, 1, x);
#define inf(x...)	dlog(_INF, 1, x);
#define dbg(x...)	dlog(_DBG, 1, x);
#define trc(x...)	dlog(_TRC, 1, x);


#define raw_nl(x...)	rlog(_RAW, 0, x);
#define err_nl(x...)	dlog(_ERR, 0, x);
#define war_nl(x...)	dlog(_WAR, 0, x);
#define inf_nl(x...)	dlog(_INF, 0, x);
#define dbg_nl(x...)	dlog(_DBG, 0, x);
#define trc_nl(x...)	dlog(_TRC, 0, x);

#define err_t(x...)	tlog(_ERR, 0, x);
#define war_t(x...)	tlog(_WAR, 0, x);
#define inf_t(x...)	tlog(_INF, 0, x);
#define dbg_t(x...)	tlog(_DBG, 0, x);
#define trc_t(x...)	tlog(_TRC, 0, x);

#define cmp1(x, y) ((x)<(y)?(x):(y))















#endif
