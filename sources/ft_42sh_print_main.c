//
// Created by Nathan on 05/02/18.
//

#include <signal.h>
#include "types.h"
#include "error.h"
#include "internal.h"
#include "library.h"

static void			ft_print_initialize_window_size(int index, uint32_t sizey, uint32_t sizex)
{
	t_text_zone		*zone;

	zone = &g_internal_context.term.zone[index];
	zone->size_y = g_internal_context.term.base.size_y * sizey / 100;
	zone->size_x = g_internal_context.term.base.size_x * sizex / 100;
}

static void			ft_print_initialize_window(int index, uint32_t posy, uint32_t posx)
{
	t_text_zone		*zone;

	zone = &g_internal_context.term.zone[index];
	zone->window = subwin(g_internal_context.term.base.window, zone->size_y, zone->size_x, posy, posx);
}

static void			ft_print_resize(int sig)
{
	(void)sig;
	endwin();

	refresh();
	clear();

	getmaxyx(stdscr, g_internal_context.term.base.size_y, g_internal_context.term.base.size_x);
	ft_print_initialize_window_size(ZONE_HISTORY, ZONE_HISTORY_Y, ZONE_HISTORY_X);
	g_internal_context.term.zone[ZONE_HISTORY].size_y -= (WINDOW_MARGE * 2);
	g_internal_context.term.zone[ZONE_HISTORY].size_x -= (WINDOW_MARGE + ZONE_MARGE);
	ft_print_initialize_window_size(ZONE_PRINT, ZONE_PRINT_Y, ZONE_PRINT_X);
	g_internal_context.term.zone[ZONE_PRINT].size_y -= (WINDOW_MARGE + ZONE_MARGE);
	g_internal_context.term.zone[ZONE_PRINT].size_x -= (WINDOW_MARGE + ZONE_MARGE);
	ft_print_initialize_window_size(ZONE_TREE, ZONE_TREE_Y, ZONE_TREE_X);
	g_internal_context.term.zone[ZONE_TREE].size_y -= (WINDOW_MARGE * 2);
	g_internal_context.term.zone[ZONE_TREE].size_x -= (WINDOW_MARGE * 2);
	ft_print_initialize_window_size(ZONE_CMD, ZONE_CMD_Y, ZONE_CMD_X);
	g_internal_context.term.zone[ZONE_CMD].size_y -= (WINDOW_MARGE * 2);
	g_internal_context.term.zone[ZONE_CMD].size_x -= (WINDOW_MARGE + ZONE_MARGE);

	curs_set(0);

	wclear(g_internal_context.term.base.window);
	wclear(g_internal_context.term.zone[ZONE_HISTORY].window);
	wclear(g_internal_context.term.zone[ZONE_PRINT].window);
	/*
	wclear(g_internal_context.term.zone[ZONE_TREE].window);
	wclear(g_internal_context.term.zone[ZONE_CMD].window);
	*/
	wresize(g_internal_context.term.base.window, g_internal_context.term.base.size_y, g_internal_context.term.base.size_x);
	wresize(g_internal_context.term.zone[ZONE_HISTORY].window, g_internal_context.term.zone[ZONE_HISTORY].size_y, g_internal_context.term.zone[ZONE_HISTORY].size_x);
	mvwin(g_internal_context.term.zone[ZONE_PRINT].window, WINDOW_MARGE, g_internal_context.term.zone[ZONE_HISTORY].size_x + ZONE_MARGE + (WINDOW_MARGE * 2));
	wresize(g_internal_context.term.zone[ZONE_PRINT].window, g_internal_context.term.zone[ZONE_PRINT].size_y, g_internal_context.term.zone[ZONE_PRINT].size_x);
	/*
	mvwin(g_internal_context.term.zone[ZONE_TREE].window, WINDOW_MARGE, g_internal_context.term.zone[ZONE_HISTORY].size_x + g_internal_context.term.zone[ZONE_PRINT].size_x + (ZONE_MARGE * 2) + (WINDOW_MARGE * 3));
	wresize(g_internal_context.term.zone[ZONE_TREE].window, g_internal_context.term.zone[ZONE_TREE].size_y, g_internal_context.term.zone[ZONE_TREE].size_x);
	mvwin(g_internal_context.term.zone[ZONE_CMD].window, g_internal_context.term.zone[ZONE_PRINT].size_y + ZONE_MARGE + (WINDOW_MARGE * 2), g_internal_context.term.zone[ZONE_HISTORY].size_x + ZONE_MARGE + (WINDOW_MARGE * 2));
	wresize(g_internal_context.term.zone[ZONE_CMD].window, g_internal_context.term.zone[ZONE_CMD].size_y, g_internal_context.term.zone[ZONE_CMD].size_x);
	*/

	box(g_internal_context.term.base.window, 0, 0);
	box(g_internal_context.term.zone[ZONE_HISTORY].window, 0, 0);
	box(g_internal_context.term.zone[ZONE_PRINT].window, 0, 0);
	/*
	box(g_internal_context.term.zone[ZONE_TREE].window, 0, 0);
	box(g_internal_context.term.zone[ZONE_CMD].window, 0, 0);
	*/

	wrefresh(g_internal_context.term.base.window);
	touchwin(g_internal_context.term.base.window);
	wrefresh(g_internal_context.term.zone[ZONE_HISTORY].window);
	touchwin(g_internal_context.term.base.window);
	wrefresh(g_internal_context.term.zone[ZONE_PRINT].window);
	touchwin(g_internal_context.term.base.window);
	wrefresh(g_internal_context.term.zone[ZONE_TREE].window);
	touchwin(g_internal_context.term.base.window);
	wrefresh(g_internal_context.term.zone[ZONE_CMD].window);

	wmove(g_internal_context.term.zone[ZONE_CMD].window, 1, 1);

	curs_set(1);
}

extern t_bool		ft_print_initialize(void)
{
	internal_context_initialize();

	/* Initialize ncurses */
	initscr();

	/* Initialize windows */
	getmaxyx(stdscr, g_internal_context.term.base.size_y, g_internal_context.term.base.size_x);
	FT_DEBUG("term size x %d y %d", g_internal_context.term.base.size_x, g_internal_context.term.base.size_y);

	g_internal_context.term.base.window = newwin(0, 0, 0, 0);

	ft_print_initialize_window_size(ZONE_HISTORY, ZONE_HISTORY_Y, ZONE_HISTORY_X);
	g_internal_context.term.zone[ZONE_HISTORY].size_y -= (WINDOW_MARGE * 2);
	g_internal_context.term.zone[ZONE_HISTORY].size_x -= (WINDOW_MARGE + ZONE_MARGE);
	ft_print_initialize_window(ZONE_HISTORY, 1, 1);
	ft_print_initialize_window_size(ZONE_PRINT, ZONE_PRINT_Y, ZONE_PRINT_X);
	g_internal_context.term.zone[ZONE_PRINT].size_y -= (WINDOW_MARGE + ZONE_MARGE);
	g_internal_context.term.zone[ZONE_PRINT].size_x -= (WINDOW_MARGE + ZONE_MARGE);
	ft_print_initialize_window(ZONE_PRINT, WINDOW_MARGE, g_internal_context.term.zone[ZONE_HISTORY].size_x + ZONE_MARGE + (WINDOW_MARGE * 2));
	/*
	ft_print_initialize_window_size(ZONE_TREE, ZONE_TREE_Y, ZONE_TREE_X);
	g_internal_context.term.zone[ZONE_TREE].size_y -= (WINDOW_MARGE * 2);
	g_internal_context.term.zone[ZONE_TREE].size_x -= (WINDOW_MARGE * 2);
	ft_print_initialize_window(ZONE_TREE, WINDOW_MARGE, g_internal_context.term.zone[ZONE_HISTORY].size_x + g_internal_context.term.zone[ZONE_PRINT].size_x + (ZONE_MARGE * 2) + (WINDOW_MARGE * 3));
	ft_print_initialize_window_size(ZONE_CMD, ZONE_CMD_Y, ZONE_CMD_X);
	g_internal_context.term.zone[ZONE_CMD].size_y -= (WINDOW_MARGE * 2);
	g_internal_context.term.zone[ZONE_CMD].size_x -= (WINDOW_MARGE + ZONE_MARGE);
	ft_print_initialize_window(ZONE_CMD, g_internal_context.term.zone[ZONE_PRINT].size_y + ZONE_MARGE + (WINDOW_MARGE * 2), g_internal_context.term.zone[ZONE_HISTORY].size_x + ZONE_MARGE + (WINDOW_MARGE * 2));
*/
	wrefresh(g_internal_context.term.base.window);

	/* Term Param */
	cbreak();
	noecho();
	curs_set(0);

	/* Set action for SIGWINCH */
	if (signal(SIGWINCH, ft_print_resize) == SIG_ERR)
		return (FALSE);
	return (TRUE);
}

extern t_bool		ft_print_finalize(void)
{
	if (!internal_context_is_initialize())
		return (FALSE);

	/* finalize windows */
	delwin(g_internal_context.term.zone[ZONE_CMD].window);
	delwin(g_internal_context.term.zone[ZONE_TREE].window);
	delwin(g_internal_context.term.zone[ZONE_PRINT].window);
	delwin(g_internal_context.term.zone[ZONE_HISTORY].window);
	delwin(g_internal_context.term.base.window);

	/* finalize ncurses */
	endwin();
	return (TRUE);
}