//
// Created by Nathan on 23/01/18.
//

#ifndef internal_H
# define internal_H

/* -- Include */
# include <pthread.h>
# include <ncurses.h>


/* -- Define */
/*
**	NB_TEXT_ZONE = nombre de zone de text au total
*/
# define NB_TEXT_ZONE	4

/*
**	Différente zone de texte avec leurs index pour le tableau de zones
**
**	ZONE_HISTORY = zone de texte de l'historique
**	ZONE_PRINT = zone de texte des résultats de commandes
**	ZONE_TREE = zone de texte du tree
**	ZONE_CMD = zone de texte de la commande tapé
*/
# define ZONE_HISTORY	0
# define ZONE_PRINT		1
# define ZONE_TREE		2
# define ZONE_CMD		3

/*
**	Différentes tailles des zones de texte en pourcentage
*/
# define ZONE_HISTORY_X		20
# define ZONE_HISTORY_Y		100
# define ZONE_PRINT_X		60
# define ZONE_PRINT_Y		80
# define ZONE_TREE_X		20
# define ZONE_TREE_Y		100
# define ZONE_CMD_X			60
# define ZONE_CMD_Y			20

# define ZONE_MARGE			2
# define WINDOW_MARGE		1


/* -- Structure */
typedef struct	s_text_zone
{
	/* -- core */
	uint32_t	size_x;
	uint32_t	size_y;
	/* -- graph */
	WINDOW		*window;
}				t_text_zone;

typedef struct	s_term
{
	t_text_zone	base;
	t_text_zone	zone[NB_TEXT_ZONE];
}				t_term;

extern t_bool		ft_print_initialize(void);
extern t_bool		ft_print_finalize(void);

#endif
