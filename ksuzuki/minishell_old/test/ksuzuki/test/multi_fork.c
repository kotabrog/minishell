/*
 * multi_fork.c
 * Copyright (C) 2014 kaoru <kaoru@bsd>
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 
#include <sys/types.h>	// fork
#include <unistd.h>	// fork
#include <sys/wait.h>	// wait
 
#include <err.h>
#include <errno.h>
 
pid_t Fork()
{
	pid_t pid = fork();
	if (-1 == pid) {
		err(EXIT_FAILURE, "can not fork");
	}
	return pid;
}
 
pid_t Waitpid(pid_t wpid, int *status, int options)
{
	for(;;){
		pid_t pid = waitpid(wpid, status, options);
		if (-1 == pid){
			if (EINTR == errno){
				(void) printf ("EINTR\n");
				continue;
			}
			if (ECHILD == errno){
				(void) printf("no child\n");
			}
			else {
				err(EXIT_FAILURE, "can not wait");
			}
		}
		return (pid);
	}
}

void wait_children (ssize_t *child) {
	int status;
	int options = WEXITED;
	bool is_first = true;

	for(;*child > 0;) {
		pid_t pid = Waitpid(-1, &status, options);
		if (-1 == pid) {
			return;
		} else if (0 == pid) {
			return;
		}
		(*child)--;
		if (is_first) {
			is_first = false;
			options = WNOHANG;
		}
	}
}

void doit()
{
	srandom( getpid() );
	unsigned int sleep_sec = random() % 3;
	sleep (sleep_sec);
}

intmain(int argc, char *argv[])
{
	const ssize_t child_max = 30;	// 同時最大子プロセス数
	const ssize_t fork_max = 70;	// forkの最大数
	ssize_t child = 0;		// 現在の子プロセスの数
	ssize_t fork_count = 0;		// 現在のfork()の回数
 
	ssize_t i = 0;
	for ( ; fork_count <= fork_max; ) {
		(void) printf ("fork_count=%lu, child=%lu\n", fork_count, child);
		for (; child < child_max; child++, fork_count++) {
			pid_t pid = Fork ();
			if (0 == pid) {
				doit();
				_exit(EXIT_SUCCESS);
			}
		}
		wait_children(&child);
	}
	while (child > 0) {
		wait_children(&child);
	}
 
	exit (EXIT_SUCCESS);
}