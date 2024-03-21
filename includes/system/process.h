#ifndef KERNEL_SYSTEM_PROCESS_H
#define KERNEL_SYSTEM_PROCESS_H

#include "utils.h"
#include "signals.h"

typedef int pid_t;
typedef int uid_t;
typedef int gid_t;

typedef struct task {
	pid_t pid;
	uid_t uid;
	gid_t gid;
	sigset_t sigmask;
} task_t;

#endif
