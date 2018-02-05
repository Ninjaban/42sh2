//
// Created by Nathan on 23/01/18.
//

#ifndef LIBRARY_H
# define LIBRARY_H

# include "internal.h"

/* -- library_configuration */
extern static struct
{
	t_bool	initialized;

	t_bool	debug_mode;

} internal_context;

/* -- Function */
/*
**	library.c
*/
extern t_bool		internal_context_is_initialize (void);
extern void			internal_context_initialize (void);

#endif