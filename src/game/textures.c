/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 00:50:11 by oligrien          #+#    #+#             */
/*   Updated: 2025/10/22 04:06:32 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static mlx_image_t	*load_tex_img(t_game *g, char *texture_path)
{
	mlx_texture_t	*tmp;
	mlx_image_t		*img;

	tmp = mlx_load_png(texture_path);
	if (!tmp)
		return (fprintf(stderr, "Error loading PNG: %s\n",
				mlx_strerror(mlx_errno)), ft_error("Couldn't load texture",
				g->map, g), NULL);
	img = mlx_texture_to_image(g->mlx, tmp);
	if (!img)
		return (mlx_delete_texture(tmp),
			ft_error("Couldn't put texture to image", g->map, g), NULL);
	return (img);
}

void	load_textures(t_game *g)
{
	g->textures->north = load_tex_img(g, g->map->north);
	g->textures->south = load_tex_img(g, g->map->south);
	g->textures->east = load_tex_img(g, g->map->east);
	g->textures->west = load_tex_img(g, g->map->west);
}

mlx_image_t	*select_texture(t_game *g, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (g->textures->west);
		else
			return (g->textures->east);
	}
	else
	{
		if (ray->dir_y > 0)
			return (g->textures->north);
		else
			return (g->textures->south);
	}
}

void	put_tex_pixel(t_game *g, t_ray *ray, int x, int y)
{
	int			index;
	uint32_t	color;

	ray->tex_y = (int)((y - g->res_h / 2 + ray->line_height / 2)
			* ((double)g->textures->sel->height / ray->line_height));
	index = ((ray->tex_y & (g->textures->sel->height - 1))
			* g->textures->sel->width + ray->tex_x) * 4;
	color = ((uint32_t)g->textures->sel->pixels[index]
			<< 24 | (uint32_t)g->textures->sel->pixels[index
			+ 1] << 16 | (uint32_t)g->textures->sel->pixels[index
			+ 2] << 8 | (uint32_t)g->textures->sel->pixels[index + 3]);
	mlx_put_pixel(g->img, x, y, color);
}
