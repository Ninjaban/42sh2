//
// Created by Nathan on 30/01/18.
//

#include "error.h"
#include "types.h"
#include "internal.h"
#include "library.h"

t_internal_context			g_internal_context = {
		.initialized = FALSE,
		.debug_mode = FALSE
};

/*
**	internal_context_is_initialize()
**
**	@param	none
**
**	@error	none
**
**	@return	TRUE in success, FALSE otherwise
*/

extern t_bool		internal_context_is_initialize(void)
{
	return (g_internal_context.initialized);
}

/*
**	internal_context_initialize()
**
**	@param	none
**
**	@error	none
*/

extern void			internal_context_initialize(void)
{
	g_internal_context.initialized = TRUE;
	g_internal_context.debug_mode = DEBUG_MODE;
}