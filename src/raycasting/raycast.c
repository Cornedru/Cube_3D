/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:50:51 by oligrien          #+#    #+#             */
/*   Updated: 2025/10/22 04:12:57 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	draw_floor_ceiling(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->res_h / 2)
	{
		x = -1;
		while (++x < g->res_w)
			mlx_put_pixel(g->img, x, y, g->ceiling_hex);
		y++;
	}
	while (y < g->res_h)
	{
		x = -1;
		while (++x < g->res_w)
			mlx_put_pixel(g->img, x, y, g->floor_hex);
		y++;
	}
}

static void	set_ray_dir(t_game *g, t_ray *ray, int x)
{
	float	camera_x;

	camera_x = 2 * x / (float)g->res_w - 1;
	ray->dir_x = g->pl->dir_x + g->pl->plane_x * camera_x;
	ray->dir_y = g->pl->dir_y + g->pl->plane_y * camera_x;
}

static void	calc_dist(t_game *g, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(g->res_h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + g->res_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + g->res_h / 2;
	if (ray->draw_end >= g->res_h)
		ray->draw_end = g->res_h - 1;
}

static void	draw_slice(t_game *g, t_ray *ray, int x)
{
	int	y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		put_tex_pixel(g, ray, x, y);
		y++;
	}
}

void	raycast_loop(t_game *g)
{
	t_ray	ray;
	int		x;

	draw_floor_ceiling(g);
	x = -1;
	while (++x < g->res_w)
	{
		set_ray_dir(g, &ray, x);
		init_dda(g, &ray);
		perform_dda(g, &ray);
		calc_dist(g, &ray);
		g->textures->sel = select_texture(g, &ray);
		if (ray.side == 0)
			ray.wall_x = g->pl->pos_y + ray.perp_wall_dist * ray.dir_y;
		else
			ray.wall_x = g->pl->pos_x + ray.perp_wall_dist * ray.dir_x;
		ray.wall_x -= floor(ray.wall_x);
		ray.tex_x = (int)(ray.wall_x * (double)g->textures->sel->width);
		if ((ray.side == 0 && ray.dir_x < 0) || (ray.side == 1
				&& ray.dir_y > 0))
			ray.tex_x = g->textures->sel->width - ray.tex_x - 1;
		draw_slice(g, &ray, x);
	}
}
