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
			mlx_strerror(mlx_errno)), 
			ft_error("Couldn't load texture", g->map, g), NULL);
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
	if (ray->side == 0)	// Hit an East/West wall
	{
		if (ray->dir_x > 0)
			return (g->textures->west);
		else
			return (g->textures->east);
	}
	else				// Hit a North/South wall
	{
		if (ray->dir_y > 0)
			return (g->textures->north);
		else
			return (g->textures->south);
	}
}

/* static uint32_t	apply_fog(uint32_t color, float distance)
{
	float		fade_amount;
	float		brightness_factor;
	t_color		rgba;

	// 1. Calculate the fade amount (0.0 to 1.0)
	// 0.0 means no fog, 1.0 means maximum fog.
	fade_amount = distance / MAX_FOG_DISTANCE;
	if (fade_amount > 1.0f)
		fade_amount = 1.0f;

	// 2. Calculate the final brightness factor using linear interpolation.
	// We start at full brightness (1.0) and subtract the fade amount
	// scaled by the total possible reduction in brightness.
	brightness_factor = 1.0f - fade_amount * (1.0f - MIN_BRIGHTNESS);

	// 3. Deconstruct the color into RGBA components
	rgba.r = (color >> 24) & 0xFF;
	rgba.g = (color >> 16) & 0xFF;
	rgba.b = (color >> 8) & 0xFF;
	rgba.a = color & 0xFF;

	// 4. Apply the brightness factor to each color component
	rgba.r = (uint8_t)(rgba.r * brightness_factor);
	rgba.g = (uint8_t)(rgba.g * brightness_factor);
	rgba.b = (uint8_t)(rgba.b * brightness_factor);

	// 5. Reconstruct the color
	return ((uint32_t)rgba.r << 24 | (uint32_t)rgba.g << 16
		| (uint32_t)rgba.b << 8 | rgba.a);
} */

void	put_tex_pixel(t_game *g, t_ray *ray, int x, int y)
{
	int			index;
	uint32_t	color;

	// This is the new, crucial calculation.
	// It calculates the texture's y-coordinate for each screen pixel y.
	// It ensures the texture is perfectly centered and scaled.
	ray->tex_y = (int)((y - g->res_h / 2 + ray->line_height / 2) * \
		((double)g->textures->sel->height / ray->line_height));

	// Get the color from the texture's pixel buffer
	// The bitwise AND is a safe way to handle tex_y going slightly out of
	// bounds due to floating point inaccuracies.
	index = ((ray->tex_y & (g->textures->sel->height - 1)) * \
			g->textures->sel->width + ray->tex_x) * 4;
	color = (
		(uint32_t)g->textures->sel->pixels[index] << 24 | 
		(uint32_t)g->textures->sel->pixels[index + 1] << 16 |
		(uint32_t)g->textures->sel->pixels[index + 2] << 8 |
		(uint32_t)g->textures->sel->pixels[index + 3]
	);

	// Apply the fog effect based on the wall's distance.
	// color = apply_fog(color, ray->perp_wall_dist);

	// Draw
	mlx_put_pixel(g->img, x, y, color);
}
