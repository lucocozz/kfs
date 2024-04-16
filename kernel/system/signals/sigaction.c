#include "system/errno.h"
#include "system/signals.h"
#include "symbol_table.h"


int sigaction(int signum, const sigaction_t *action, sigaction_t *old_action)
{
	if (!valide_signal(signum) || siginmask(signum, SIG_KERNEL_ONLY_MASK))
		return (-EINVAL);

	//TODO: getting current process and spinlockhim

	if (old_action != NULL) {
		old_action->handler = g_sigaction[signum].handler;
		old_action->mask = g_sigaction[signum].mask;
		old_action->flags = g_sigaction[signum].flags;
	}
	
	if (action != NULL) {
		g_sigaction[signum].handler = action->handler;
		g_sigaction[signum].mask = action->mask;
		g_sigaction[signum].flags = action->flags;
	}

	return (0);
}
EXPORT_SYMBOL(sigaction);
