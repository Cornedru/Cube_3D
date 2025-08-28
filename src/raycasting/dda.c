/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 01:05:17 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/28 03:56:14 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	set_deltadist(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabsf(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabsf(1 / ray->dir_y);
}

static void	set_step_sidedist(t_game *g, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (g->pl->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - g->pl->pos_x) \
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (g->pl->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - g->pl->pos_y) \
			* ray->delta_dist_y;
	}
}

void	init_dda(t_game *g, t_ray *ray)
{
	ray->map_x = (int)g->pl->pos_x;
	ray->map_y = (int)g->pl->pos_y;
	set_deltadist(ray);
	set_step_sidedist(g, ray);
}

static void	increment_ray(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	perform_dda(t_game *g, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		increment_ray(ray);
		if (is_oob(g, ray->map_x, ray->map_y))
		{
			hit = 1;
			continue ;
		}
		if (g->map->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}
