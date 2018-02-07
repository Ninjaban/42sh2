//
// Created by Nathan on 07/02/18.
//

#include "types.h"
#include "internal.h"
#include "library.h"

int		main()
{
	ft_print_initialize();
	box(g_internal_context.term.base.window, 0, 0);
	wrefresh(g_internal_context.term.base.window);

	box(g_internal_context.term.zone[ZONE_HISTORY].window, 0, 0);
	touchwin(g_internal_context.term.base.window);
	wrefresh(g_internal_context.term.zone[ZONE_HISTORY].window);
	box(g_internal_context.term.zone[ZONE_PRINT].window, 0, 0);
	touchwin(g_internal_context.term.base.window);
	wrefresh(g_internal_context.term.zone[ZONE_PRINT].window);
	box(g_internal_context.term.zone[ZONE_TREE].window, 0, 0);
	touchwin(g_internal_context.term.base.window);
	wrefresh(g_internal_context.term.zone[ZONE_TREE].window);
	box(g_internal_context.term.zone[ZONE_CMD].window, 0, 0);
	touchwin(g_internal_context.term.base.window);
	wmove(g_internal_context.term.zone[ZONE_CMD].window, 1, 1);
	curs_set(1);
	wrefresh(g_internal_context.term.zone[ZONE_CMD].window);

	while (1)
		;
	ft_print_finalize();
	return (0);
}