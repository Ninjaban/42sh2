//
// Created by Nathan on 23/01/18.
//

#ifndef LIBRARY_H
# define LIBRARY_H

/*
** -- library_configuration
*/
typedef struct	s_internal_context
{
	t_bool		initialized;

	t_bool		debug_mode;

	t_term		term;
}				t_internal_context;

extern t_internal_context g_internal_context;

/* -- Function */
/*
**	library.c
*/
extern t_bool		internal_context_is_initialize (void);
extern void			internal_context_initialize (void);

#endif
