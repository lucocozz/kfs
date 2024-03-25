#ifndef KERNEL_SYSTEM_SIGNALS_H
#define KERNEL_SYSTEM_SIGNALS_H

#include "system/utils.h"
#include "system/process.h"

#define _NSIG 20 // Number of signals used

#define SIG_MASK(sig)	(1UL << sig)  // Mask for a signal
#define SIG_UNMASK(sig)	~(1UL << sig) // Unmask for a signal

#define SIGHUP		 1 // Abort - Hangup of controlling terminal or process
#define SIGINT		 2 // Abort - Interrupt from keyboard
#define SIGQUIT		 3 // Dump - Quit from keyboard
#define SIGILL		 4 // Dump - Illegal Instruction
#define SIGTRAP		 5 // Dump - Trace/breakpoint trap
#define SIGABRT		 6 // Dump - Abort signal from abort(3)
#define SIGIOT		 6 // Dump - Equivalent to SIGABRT
#define SIGBUS		 7 // Dump - Bus error (bad memory access)
#define SIGFPE		 8 // Dump - Floating point exception
#define SIGKILL		 9 // Abort - Force process termination
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

#define	SIG_DFL		((void (*)(int))  0) // Default signal
#define	SIG_IGN		((void (*)(int))  1) // Ignored signal
#define	SIG_ERR		((void (*)(int)) -1) // Signal Error
#define	SIG_HOLD	((void (*)(int))  3) // Hold signal

#define SIG_KERNEL_ONLY_MASK (sigmask(SIGKILL) | sigmask(SIGSTOP))


typedef union sigval {
	int		sigval_int;
	void	*sigval_ptr;
} sigval_t;

typedef struct sigset {
	uint32_t sig[2]; //Used like 64bits
} sigset_t;

typedef void (*sighandler_t)(int);
typedef void (*sigrestore_t)(void);

/// @brief Signal action
/// @note Used to store information about a signal action
typedef struct sigaction {
	sighandler_t	handler;
	sigset_t		mask;
	uint32_t		flags;
} sigaction_t;

typedef struct k_sigaction {
	sighandler_t	handler;
	sigrestore_t	restorer;
	sigset_t		mask;
	uint32_t		flags;
} k_sigaction_t;

// typedef struct signal {
// 	atomic_t			count;
// 	struct k_sigaction	action[_NSIG];
// 	spinlock_t			siglock;
// } signal_t;

/// @brief Signal information
/// @note Used to store information about a signal
typedef struct siginfo {
	int		signo;	// Signal number
	int		errno;	// An errno value
	int		code;	// Signal code
	pid_t	pid;	// Sending process ID
	uid_t	uid;	// Real user ID of sending process
	void 	*addr;	// Address of faulting instruction
	int		status;	// Exit value or signal
	int		band;	// Band event for SIGPOLL
} siginfo_t;

/// @brief Signal queue
/// @note Used to store signals that are pending for a process
typedef struct signal_queue {
	siginfo_t 			info;
	struct signal_queue *next;
} signal_queue_t;

typedef struct sighand {
	sigaction_t	action[_NSIG];
} sighand_t;

typedef struct sigpending {
	sigset_t		mask;
	signal_queue_t	*queue;
} sigpending_t;


extern sigaction_t	g_sigaction[_NSIG];
extern sighandler_t	g_default_sigaction[_NSIG];


/// @brief Add a signal to the set
/// @param set The set to add the signal to
/// @param signum The signal to add
static inline void sigaddset(sigset_t *set, int signum) {
	signum -= 1;
	set->sig[signum / 32] |= 1 << (signum % 32);
}

/// @brief Remove a signal from the set
/// @param set The set to remove the signal from
/// @param signum The signal to remove
static inline void sigdelset(sigset_t *set, int signum) {
	signum -= 1;
	set->sig[signum / 32] &= ~(1 << (signum % 32));
}

/// @brief Set the signal mask
/// @param set The set to set the mask for
/// @param mask The mask to set
static inline void sigsetmask(sigset_t *set, int mask) {
	set->sig[0] |= mask;
}

/// @brief Remove the signal mask
/// @param set The set to remove the mask for
/// @param mask The mask to remove
static inline void sigdelmask(sigset_t *set, int mask) {
	set->sig[0] &= ~mask;
}

/// @brief Check if a signal is in the set
/// @param set The set to check
/// @param signum The signal to check
/// @return 1 if the signal is in the set, 0 otherwise
static inline int sigismember(sigset_t *set, int signum) {
	signum -= 1;
	return (1 & (set->sig[signum / 32] >> (signum % 32)));
}

/// @brief Create a signal mask
/// @param signum The signal to create the mask for
static inline uint32_t sigmask(int signum) {
	return (1UL << (signum - 1));
}

/// @brief Empty the signal set (set all signals to 0)
/// @param set The set to empty
static inline void sigemptyset(sigset_t *set) {
	sigsetmask(set, 0);
}

/// @brief Fill the signal set with all signals
/// @param set The set to fill
static inline void sigfillset(sigset_t *set) {
	sigsetmask(set, 0xFFFFFFFF);
}

/// @brief Check if a signal is valid
/// @param signum The signal to check
static inline int valide_signal(int signum) {
	return (signum > 0 && signum <= _NSIG ? 1 : 0);
}

/// @brief Check if a signal is in the mask
/// @param signum The signal to check
static inline int siginmask(int signum, int mask) {
	return (valide_signal(signum) && (sigmask(signum) & mask));
}

void			signals_init(void);
sighandler_t	signal(int signum, sighandler_t handler);
int				sigaction(int signum, const sigaction_t *action, sigaction_t *old_action);
void			do_signal(int signum);

//dequeue_signal()
//handle_signal()
//send_sig_info()

void	signal_default_handler(int signum);
void	sigfpe_default_handler(int signum);


#endif
