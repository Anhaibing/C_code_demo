#include <pthread.h>
#include "user_fifo_test.h"
#include "../common/misc.h"

int cmd_pipe[2] = {-1, -1};
pthread_t thread[2];

int cmd_fifo_init () {
	int ret = pipe (cmd_pipe);
	if (ret < 0) {
		printf ("cmd_pipe init failed!\n");
		return -1;
	}
	printf ("cmd_pipe init success!\n");
	return 0;
}

int duerLedSet_handle () {
	printf ("I get pipe data!\n");
}

cmd_item_t unfifo_cmd_tbl[] = {
	ADD_HANDLE_ITEM(duerLedSet, NULL)
	{0}
};

void* cmd_control (void *ptr) {
	user_fifo_write_fmt(cmd_pipe, "duerLedSet 1");
}

void* cmd_parse (void *ptr) {
	fifo_cmd_t pipe_cmd_args = {
		.type = FIFO_CMD_UNSPECIFIED_PIPE,
		.fd   = cmd_pipe[0],
		.tbl  = unfifo_cmd_tbl
	};
	int ret = user_fifo_read_init(&pipe_cmd_args);
	if (ret < 0) {
		printf ("user_fifo_read_init failed\n");
		return;
	}
	user_fifo_read_proc(&pipe_cmd_args);
}

void thread_create () {
	pthread_attr_t a_thread_attr;
	pthread_attr_init (&a_thread_attr);
	pthread_attr_setstacksize (&a_thread_attr, PTHREAD_STACK_MIN * 4);
	memset (&thread, 0, sizeof(thread));

	if (pthread_create(&thread[0], &a_thread_attr, cmd_control, NULL) != 0)
		printf ("cmd_control_pthread create failed!\n");
	else {
		printf ("cmd_control_pthread create success!\n");
		pthread_setname_np (thread[0], "cmd_control");
	}

	if (pthread_create(&thread[1], &a_thread_attr, cmd_parse, NULL) != 0)
		printf ("cmd_parse_pthread create failed!\n");
	else {
		printf ("cmd_parse_pthread create success!\n");
		pthread_setname_np (thread[1], "cmd_control");
	}
}

void thread_wait () {
	if (!thread[0])
		pthread_join (thread[0], NULL);
	if (!thread[1])
		pthread_join (thread[1], NULL);
}

void cmd_fifo_free () {
	if (cmd_pipe[0] > 0)
		close (cmd_pipe[0]);
	if (cmd_pipe[1] > 0)
		close (cmd_pipe[1]);
}

unixFifoOps_t* fifo_ptr;

int user_fifo_test () {
	//fifo_ptr = user_fifo_write_init("USERFIFOTEST_FIFO");
	//if (!fifo_ptr)
	//	return -1;
	//inf ("user_fifo_write_init success!");

	//user_fifo_write_fmt(fifo_ptr, "Testfifoset 1");

	cmd_fifo_init ();
	thread_create ();
	thread_wait ();
	cmd_fifo_free ();
	return 0;
}
