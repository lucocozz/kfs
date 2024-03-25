#include "system/signals.h"
#include "symbol_table.h"


void	do_signal(int signum)
{
	if (!valide_signal(signum) && g_sigaction[signum].handler == SIG_IGN)
		return;
	
	if (g_sigaction[signum].handler == SIG_DFL) {
		if (g_default_sigaction[signum] != SIG_DFL)
			g_default_sigaction[signum](signum);
	}
	else
		g_sigaction[signum].handler(signum);
	
	if (g_sigaction[signum].flags & SA_RESETHAND) {
		g_sigaction[signum].handler = SIG_DFL;
		g_sigaction[signum].flags = 0;
	}
}
