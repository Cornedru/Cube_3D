/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:50:51 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/28 03:47:20 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	draw_floor_ceiling(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H / 2)	// Draw the ceiling
	{
		x = -1;
		while (++x < WIN_W)
			mlx_put_pixel(g->img, x, y, CEILING_COLOR);
		y++;
	}
	while (y < WIN_H)	// Draw the floor
	{
		x = -1;
		while (++x < WIN_W)
			mlx_put_pixel(g->img, x, y, FLOOR_COLOR);
		y++;
	}
}

static void	set_ray_dir(t_game *g, t_ray *ray, int x)
{
	float	camera_x;

	camera_x = 2 * x / (float)WIN_W - 1;
	ray->dir_x = g->pl->dir_x + g->pl->plane_x * camera_x;
	ray->dir_y = g->pl->dir_y + g->pl->plane_y * camera_x;
}

static void	calc_dist(t_ray *ray)
{
	int line_height;

	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	line_height = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = -line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

static void	draw_slice(t_game *g, t_ray *ray, int x)
{
	int		y;
	int		color;

	if (ray->side == 0)
		color = WALL_NS;
	else
		color = WALL_EW;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		mlx_put_pixel(g->img, x, y, color);
		y++;
	}
}

void	raycast_loop(t_game *g)
{
	t_ray	ray;
	int		x;

	draw_floor_ceiling(g);
	x = -1;
	while (++x < WIN_W)
	{
		set_ray_dir(g, &ray, x);
		init_dda(g, &ray);
		perform_dda(g, &ray);
		calc_dist(&ray);
		draw_slice(g, &ray, x);
	}
}
