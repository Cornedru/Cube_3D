/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:11:52 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/27 23:42:20 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	set_north(t_player *pl)
{
	pl->dir_x = 0;
	pl->dir_y = -1;
	pl->plane_x = FOV;
	pl->plane_y = 0;
}

static void	set_south(t_player *pl)
{
	pl->dir_x = 0;
	pl->dir_y = 1;
	pl->plane_x = -FOV;
	pl->plane_y = 0;
}

static void	set_east(t_player *pl)
{
	pl->dir_x = 1;
	pl->dir_y = 0;
	pl->plane_x = 0;
	pl->plane_y = FOV;
}

static void	set_west(t_player *pl)
{
	pl->dir_x = -1;
	pl->dir_y = 0;
	pl->plane_x = 0;
	pl->plane_y = -FOV;
}

void	init_player_direction(t_game *g)
{
	if (g->pl->start_dir == 'N')
		set_north(g->pl);
	else if (g->pl->start_dir == 'S')
		set_south(g->pl);
	else if (g->pl->start_dir == 'E')
		set_east(g->pl);
	else if (g->pl->start_dir == 'W')
		set_west(g->pl);
}
