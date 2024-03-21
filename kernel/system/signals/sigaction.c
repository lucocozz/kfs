#include "system/errno.h"
#include "system/signals.h"

int sigaction(int signum, const sigaction_t *action, sigaction_t *old_action)
{
	UNUSED(old_action);
	if (!valide_signal(signum) || siginmask(signum, SIG_KERNEL_ONLY_MASK))
		return (-EINVAL);

	//TODO: getting current process and spinlockhim
	if (action->handler == SIG_IGN) {
		sigset_t mask;

		sigemptyset(&mask);
		sigaddset(&mask, signum);
	}

	return (0);
}
