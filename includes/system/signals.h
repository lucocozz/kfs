#ifndef KERNEL_SYSTEM_SIGNALS_H
#define KERNEL_SYSTEM_SIGNALS_H

#include "system/utils.h"

#define _NSIG 20 // Number of signals used

#define SIG_MASK(sig) (1UL << sig)
#define SIG_UNMASK(sig) (1UL << sig)

#define SIGHUP		1 // Abort - Hangup of controlling terminal or process
#define SIGINT		2 // Abort - Interrupt from keyboard
#define SIGQUIT		3 // Dump - Quit from keyboard
#define SIGILL		4 // Dump - Illegal Instruction
#define SIGTRAP		5 // Dump - Trace/breakpoint trap
#define SIGABRT		6 // Dump - Abort signal from abort(3)
#define SIGIOT		6 // Dump - Equivalent to SIGABRT
#define SIGBUS		7 // Dump - Bus error (bad memory access)
#define SIGFPE		8 // Dump - Floating point exception
#define SIGKILL		9 // Abort - Force process termination
#define SIGUSR1		10 // Abort - User-defined signal 1
#define SIGSEGV		11 // Dump - Invalid memory reference
#define SIGUSR2		12 // Abort - User-defined signal 2
#define SIGPIPE		13 // Abort - Broken pipe: write to pipe with no readers
#define SIGALRM		14 // Abort - Timer signal from alarm(2)
#define SIGTERM		15 // Abort - Termination signal
#define SIGSTKFLT	16 // Abort - Stack fault on coprocessor (unused)
#define SIGCHLD		17 // Ignore - Child stopped or terminated
#define SIGCONT		18 // Continue - Continue if stopped
#define SIGSTOP		19 // Stop - Stop process
#define SIGTSTP		20 // Stop - Stop typed at terminal
#define SIGTTIN		21 // Stop - Terminal input for background process
#define SIGTTOU		22 // Stop - Terminal output for background process
#define SIGURG		23 // Ignore - Urgent condition on socket (4.2BSD)
#define SIGXCPU		24 // Dump - CPU time limit exceeded (4.2BSD)
#define SIGXFSZ		25 // Dump - File size limit exceeded (4.2BSD)
#define SIGVTALRM	26 // Abort - Virtual alarm clock (4.2BSD)
#define SIGPROF		27 // Abort - Profiling timer expired
#define SIGWINCH	28 // Ignore - Window resize signal (4.3BSD, Sun)
#define SIGIO		29 // Abort - I/O now possible (4.2BSD)
#define SIGPWR		30 // Abort - Power failure (System V)
#define SIGSYS		31 // Dump - Bad system call (SVr4)

#define SA_NOCLDSTOP	(1UL << 1) // Do not send SIGCHLD to the parent when the process is stopped.
#define SA_NODEFER		(1UL << 2) // Do not mask the signal while executing the signal handler.
#define SA_NOMASK		(1UL << 2) // Do not mask the signal while executing the signal handler.
#define SA_RESETHAND	(1UL << 3) // Reset to default action after executing the signal handler.
#define SA_ONESHOT		(1UL << 3) // Reset to default action after executing the signal handler.
#define SA_ONSTACK		(1UL << 4) // Use an alternate stack for the signal handler.
#define SA_RESTART		(1UL << 5) // Interrupted system calls are automatically restarted.
#define SA_SIGINFO		(1UL << 6) // Provide additional information to the signal handler.

#define sigaddset(set, nsig) set->sig[(nsig - 1) / 32] |= SIG_MASK((nsig - 1) % 32)
#define sigdelset(set, nsig) set->sig[(nsig - 1) / 32] &= SIG_UNMASK((nsig - 1) % 32)
#define sigaddsetmask(set, mask) set->sig[0] |= mask
#define sigdelsetmask(set, mask) set->sig[0] &= ~mask
#define sigismember(set, nsig) 1 & (set->sig[(nsig - 1) / 32] >> ((nsig - 1) % 32))
// #define sigmask(nsig)

typedef void (*sighandler_t)(int);

typedef struct sigset_s {
	uint32_t sig[2]; //Used like 64bits
} sigset_t;

typedef struct sigaction {
	sighandler_t	handler;
	sigset_t		mask;
	uint32_t		flags;
} sigaction_t;

// typedef signal_struct {
// 	atomic_t			count;
// 	struct k_sigaction	action[_NSIG];
// 	spinlock_t			siglock;
// };

typedef struct signal_queue {
	siginfo_t 			info;
	struct signal_queue *next;
} signal_queue_t;

#endif
