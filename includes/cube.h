/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:45:56 by ndehmej           #+#    #+#             */
/*   Updated: 2025/08/22 02:31:00 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

/* includes ***************************************************************** */

# include "../gc/includes/gc.h"
# include "../libft/includes/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_textures {
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	t_color	floor;
	t_color	ceiling;
}	t_textures;

typedef struct s_map
{
	char			**map;
	int				x_len;
	int				y_len;
	int				c_count;
	int				e_count;
	int				p_count;
	int				p_y;
	int				p_x;
}					t_map;

typedef struct s_game
{
	char			**map;
	int				map_width;
	int				map_height;
	mlx_t			*mlx;
	mlx_image_t		*p;
	mlx_image_t		*wall;
	int				p_y;
	int				p_x;
	unsigned int	move_count;
	t_textures		*textures;
}					t_game;

void				delete_texture_img(t_game *game);
void				clear_map(t_map *map);
int					parse_file(char *file, t_game	*game);
int					check_args(int argc, char **argv);
void				ft_error(char *message, t_map *map, t_game *game);
void				clear_map(t_map *map);
void				delete_texture_img(t_game *game);
void				ft_error(char *message, t_map *map, t_game *game);
void				check_map(t_map *map);
void				check_path_closed(t_map *map);
void				store_map(t_map *map, t_textures *textures, char **av);
void				parse_config_line(char *line, t_textures *textures);
void				parse_color(char *line, t_color *color);
void				read_config_and_map(const char *file, t_map *map, t_textures *textures);
void				display_map(t_game *game, t_map *map, int x, int y);
void				init_textures(t_game *game, t_map *map);
void				ft_hook(mlx_key_data_t key, void *param);

#endif