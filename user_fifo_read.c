/* func: fifo data parse to cmd and argv
 * desc: 
 * auth: haibing.an1991@gmail.com
 * data: 2018-11-29
 * note: none
 */


#include "user_fifo.h"
#include "slog.h"
#include "misc.h"

int user_fifo_read_init(fifo_cmd_t *pArgs) {
	switch (pArgs->type) {
		case FIFO_CMD_UNSPECIFIED_FIFO:
		case FIFO_CMD_SPECIFIED_FIFO:{
			pArgs->opt_ptr = unix_fifo_ops_create (pArgs->path, 0);
			if (!pArgs->opt_ptr)
				return -1;
			return 0;
			}
		case FIFO_CMD_UNSPECIFIED_PIPE:
		case FIFO_CMD_SPECIFIED_PIPE:{
			unixFifoOps_t *ptr = calloc (1, sizeof(unixFifoOps_t));
			if (!ptr) {
				err ("calloc failed!");
				return -2;
			}
			ptr->fd = pArgs->fd;
			pArgs->opt_ptr = ptr;
			return 0;
			}
		default:
			return -2;
	}
}

static int user_fifo_cmd_handle(fifo_cmd_t* pArgs,char *buf,size_t len){
	int ret = 0, argc = 0, cmplen = 0;
	item_arg_t item_arg = {0};
	dbg ("arg1:%s", buf);
	char **argv = argl_to_argv (buf, &argc);
	if (!argv)
		return -1;
	size_t i = 0;
	for (;!pArgs->tbl[i].cmd; i++) {
		cmplen = ANBIN_MIN(strlen(argv[0]), strlen(pArgs->tbl[i].cmd));
		if (strncmp(pArgs->tbl[i].cmd, argv[0], cmplen))
			continue;
		item_arg.argc = argc;
		item_arg.argv = argv;
		item_arg.args = pArgs->tbl[i].args;
		ret = pArgs->tbl[i].handle(&item_arg);
		ret = ret < 0 ? -2:0;
		goto exit;
	}
	ret = -3;
exit:
	if (0 == ret)		{dbg ("%s excute succeed!", argv[0]);}
	else if (-2 == ret)	{err ("%s excute failed!", argv[0]);}
	else if (-3 == ret)	{err ("%s not found!", argv[0]);}
	FREE(argv);
	return ret;

}

int user_fifo_read_proc(fifo_cmd_t *pArgs) {
	char buf[1024] = "";
	for (;;) {
		bzero (buf, sizeof(buf));
		int get_len = unix_fifo_ops_read (pArgs->opt_ptr, buf, sizeof(buf));
		if (get_len > 0) {
			char *idx = buf - FMT_SUBFFIX_LEN;
			char *cmd = NULL;
			for (;;) {
				cmd = idx = memmem (idx + FMT_SUBFFIX_LEN, buf + get_len - idx - FMT_SUBFFIX_LEN, FMT_PREFIX, FMT_PREFIX_LEN);
				if (!cmd)
					break;
				idx = memmem (cmd + FMT_PREFIX_LEN, buf + get_len - idx - FMT_PREFIX_LEN, FMT_SUBFFIX, FMT_SUBFFIX_LEN);
				if (!idx)
					break;
				if (pArgs->handle) {
					pArgs->handle (cmd + FMT_PREFIX_LEN, idx - cmd - FMT_PREFIX_LEN);
					continue;
				}
				user_fifo_cmd_handle (pArgs, cmd + FMT_SUBFFIX_LEN, idx - cmd - FMT_PREFIX_LEN);
			}
		}
	}
}
