/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:45:56 by ndehmej           #+#    #+#             */
/*   Updated: 2025/08/28 03:54:25 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

/* includes ***************************************************************** */

# include "../gc/includes/gc.h"
# include "../libft/includes/libft.h"
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"


# define WIN_W 720
# define WIN_H 360

# define FOV 0.66
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05

# define CEILING_COLOR 0x688898FF	// A grayish blue
# define FLOOR_COLOR 0x504030FF		// A brownish color
# define WALL_NS 0xAA2222FF
# define WALL_EW 0x882222FF

typedef struct s_key
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
}	t_key;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	t_color	floor;
	t_color	ceiling;
}	t_textures;

typedef struct s_map
{
	char	**map;
	int		x_len;
	int		y_len;
	int		p_y;
	int		p_x;
}	t_map;

typedef struct s_player
{
	// Current position on the map
	float	pos_x;
	float	pos_y;

	// Direction vector
	float	dir_x;
	float	dir_y;

	// Camera plane vector (defines FOV)
	float	plane_x;
	float	plane_y;

	// The 'N', 'S', 'E', or 'W' from the map
	char	start_dir; 

	// Movement
	t_key	keys;
	float	d_x;
	float	d_y;

}	t_player;

typedef struct s_ray
{
	// Ray direction
	float	dir_x;
	float	dir_y;

	// DDA
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side; // Was a NS or a EW wall hit?

	// Drawing
	int		draw_start;
	int		draw_end;

}	t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			*map;
	t_player		*pl;
	t_textures		*textures;
}	t_game;

// parser
void	delete_texture_img(t_game *game);
int		parse_file(char *file, t_game	*game);
int		check_args(int argc, char **argv);
void	ft_error(char *message, t_map *map, t_game *game);
void	clear_map(t_map *map);
void	delete_texture_img(t_game *game);
void	check_map(t_game *g);
void	check_path_closed(t_map *map);
void	store_map(t_game *g, char **av);
void	parse_config_line(char *line, t_textures *textures);
void	read_config_and_map(const char *file, t_map *map, t_textures *textures);
void	display_map(t_game *game, t_map *map, int x, int y);
void	init_textures(t_game *game, t_map *map);

// utils.c
void	clear_map(t_map *map);
void	ft_error(char *message, t_map *map, t_game *game);
bool	is_oob(t_game *g, int map_x, int map_y);
void	init_player_data(t_game *g, int x, int y, char c);

// game
//	game.c
int		init_game(t_game *g);

//	player_init.c
void	init_player_direction(t_game *g);

//	move.c
void	update_player_state(t_game *g);

// raycasting
//	raycast.c
void	raycast_loop(t_game *g);

//	dda.c
void	init_dda(t_game *g, t_ray *ray);
void	perform_dda(t_game *g, t_ray *ray);


#endif