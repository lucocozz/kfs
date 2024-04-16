#include "system/signals.h"
#include "symbol_table.h"


sigaction_t		g_sigaction[_NSIG] = {0};
sighandler_t	g_default_sigaction[_NSIG] = {0};


void	signals_init(void)
{
	for (int i = 0; i < _NSIG; ++i) {
		g_default_sigaction[i] = signal_default_handler;
	}
}
EXPORT_SYMBOL(signals_init);
