/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 03:11:01 by oligrien          #+#    #+#             */
/*   Updated: 2025/10/22 01:55:53 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

/* static void	rotate_player(t_player *pl, float dir)
{
	float	old_dir_x;
	float	old_plane_x;
	float	angle;

	angle = ROT_SPEED * dir;
	old_dir_x = pl->dir_x;
	pl->dir_x = pl->dir_x * cos(angle) - pl->dir_y * sin(angle);
	pl->dir_y = old_dir_x * sin(angle) + pl->dir_y * cos(angle);
	old_plane_x = pl->plane_x;
	pl->plane_x = pl->plane_x * cos(angle) - pl->plane_y * sin(angle);
	pl->plane_y = old_plane_x * sin(angle) + pl->plane_y * cos(angle);
} */

static void	rotate_player(t_player *pl, int dir)
{
	float	old_dir_x;
	float	old_plane_x;
	float	sinus;

	if (dir > 0)
		sinus = SIN;
	else
		sinus = -SIN;
	old_dir_x = pl->dir_x;
	pl->dir_x = pl->dir_x * COS - pl->dir_y * sinus;
	pl->dir_y = old_dir_x * sinus + pl->dir_y * COS;
	old_plane_x = pl->plane_x;
	pl->plane_x = pl->plane_x * COS - pl->plane_y * sinus;
	pl->plane_y = old_plane_x * sinus + pl->plane_y * COS;
}

static void check_collision(t_game *g, float new_x, float new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)g->pl->pos_y;
	if (!is_oob(g, map_x, map_y))
	{
		if (g->map->map[map_y][map_x] != '1')
			g->pl->pos_x = new_x;
	}
	map_x = (int)g->pl->pos_x;
	map_y = (int)new_y;
	if (!is_oob(g, map_x, map_y))
	{
		if (g->map->map[map_y][map_x] != '1')
			g->pl->pos_y = new_y;
	}
}

static void	move_player(t_game *g)
{
	g->pl->d_x = 0;
	g->pl->d_y = 0;
	if (g->pl->keys.w)
	{
		g->pl->d_x += g->pl->dir_x * MOVE_SPEED;
		g->pl->d_y += g->pl->dir_y * MOVE_SPEED;
	}
	if (g->pl->keys.s)
	{
		g->pl->d_x -= g->pl->dir_x * MOVE_SPEED;
		g->pl->d_y -= g->pl->dir_y * MOVE_SPEED;
	}
	if (g->pl->keys.d)
	{
		g->pl->d_x += g->pl->plane_x * MOVE_SPEED;
		g->pl->d_y += g->pl->plane_y * MOVE_SPEED;
	}
	if (g->pl->keys.a)
	{
		g->pl->d_x -= g->pl->plane_x * MOVE_SPEED;
		g->pl->d_y -= g->pl->plane_y * MOVE_SPEED;
	}
	check_collision(g, g->pl->pos_x + g->pl->d_x, g->pl->pos_y + g->pl->d_y);
}

void	update_player_state(t_game *g)
{
	if (g->pl->keys.right)
		rotate_player(g->pl, 1);
	if (g->pl->keys.left)
		rotate_player(g->pl, -1);
	move_player(g);
}
