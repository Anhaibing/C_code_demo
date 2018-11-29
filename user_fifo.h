#ifndef USER_FIFO_H_
#define USER_FIFO_H_

#include "unix_fifo_ops.h"

#define FMT_PREFIX		"^"		//protocol head
#define FMT_SUBFFIX		"\n"	//protocol tail
#define FMT_PREFIX_len	(sizeof(FMT_PREFIX) - 1)
#define FMT_SUBFFIX_len	(sizeof(FMT_SUBFFIX) - 1)

typedef enmu fifo_cmd_type_t {
	FIFO_CMD_TYPE_MIN,
	FIFO_CMD_UNSPECIFIED_FIFO,
	FIFO_CMD_UNSPECIFIED_PIPE,
	FIFO_CMD_SPECIFIED_FIFO,
	FIFO_CMD_SPECIFIED_PIPE,
	FIFO_CMD_TYPE_MAX
} fifo_cmd_type_t;

typedef struct item_arg_t {
	int argc;
	char **argv;
	void *args;
} item_arg_t;

typedef struct cmd_item_t {
	const char *cmd;
	int (*handle)(item_arg_t *);
	void *args;
} cmd_item_t;

typedef struct fifo_cmd_t {
	fifo_cmd_type_t type;
	char* path;
	cmd_item_t* tbl;
	int fd;
	int (*handle)(char *, int);
	unixFifoOps_t *opt_ptr;
} fifo_cmd_t;

unixFifoOps_t *user_fifo_write_init (const char *path);
int user_fifo_write_str (unixFifoOps_t* ptr, char *contex);
int user_fifo_write_fmt (unixFifoOps_t* ptr, const char *fmt, ...);
int user_fifo_write_fmt_len (unixFifoOps_t* ptr, siez_t len, const char *fmt, ...);
int user_fifo_read_init (fifo_cmd_t *pArgs);
int user_fifo_read_proc (fifo_cmd_t *pArgs);
int user_fifo_write_str ();

#endif
