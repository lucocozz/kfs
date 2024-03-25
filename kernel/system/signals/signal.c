#include "system/signals.h"
#include "symbol_table.h"


sighandler_t	signal(int signum, sighandler_t handler)
{
	sigaction_t action;
	sigaction_t old_action;

	if (!valide_signal(signum) || siginmask(signum, SIG_KERNEL_ONLY_MASK))
		return (SIG_ERR); //TODO: set errno to EINVAL

	sigemptyset(&action.mask);
	action.flags = 0;
	action.handler = handler;

	if (sigaction(signum, &action, &old_action) < 0)
		return (SIG_ERR);
	return (old_action.handler);
}
EXPORT_SYMBOL(signal);
