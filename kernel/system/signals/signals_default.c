#include "system/signals.h"
#include "symbol_table.h"

static const char *sig_default_message[] = {
	[SIGHUP] = "Hangup",
	[SIGINT] = "Interrupt",
	[SIGQUIT] = "Quit",
	[SIGILL] = "Illegal instruction",
	[SIGTRAP] = "Trap",
	[SIGABRT] = "Aborted",
	[SIGBUS] = "Bus error",
	[SIGFPE] = "Divide by zero",
	[SIGKILL] = "Killed",
	[SIGUSR1] = "User signal 1",
	[SIGSEGV] = "Segmentation fault",
	[SIGUSR2] = "User signal 2",
	[SIGPIPE] = "Broken pipe",
	[SIGALRM] = "Alarm",
	[SIGTERM] = "Terminated",
	[SIGSTKFLT] = "Stack fault",
	[SIGCHLD] = "Child status changed",
	[SIGCONT] = "Continued",
	[SIGSTOP] = "Stopped",
	[SIGTSTP] = "Stopped",
	[SIGTTIN] = "Stopped",
	[SIGTTOU] = "Stopped",
	[SIGURG] = "Urgent",
	[SIGXCPU] = "CPU time limit exceeded",
	[SIGXFSZ] = "File size limit exceeded",
	[SIGVTALRM] = "Virtual timer expired",
	[SIGPROF] = "Profiling timer expired",
	[SIGWINCH] = "Window size changed",
	[SIGIO] = "I/O now possible",
	[SIGPWR] = "Power failure",
	[SIGSYS] = "Bad system call",
};


void	sigfpe_default_handler(int signum)
{
	UNUSED(signum);
	panic("Divide by zero");
}
EXPORT_SYMBOL(sigfpe_default_handler);


void	signal_default_handler(int signum)
{
	if (signum < _NSIG && sig_default_message[signum] != NULL)
		panic(sig_default_message[signum]);
	else
		panic("Unhandled signal");
}
EXPORT_SYMBOL(signal_default_handler);