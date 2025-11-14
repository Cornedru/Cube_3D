/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:45:56 by ndehmej           #+#    #+#             */
/*   Updated: 2025/10/22 04:29:22 by oligrien         ###   ########.fr       */
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


# define WIN_W 1920
# define WIN_H 1080

# define FOV 0.66
# define MAX_FOG_DISTANCE 15.0
# define MIN_BRIGHTNESS 0.2f

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05
# define SIN sin(ROT_SPEED)
# define COS cos(ROT_SPEED)

# define CEILING_COLOR 0x688898FF	// A grayish blue
# define FLOOR_COLOR 0x504030FF		// A brownish color
# define WALL_NS 0xAA2222FF
# define WALL_EW 0x882222FF


/* typedef ****************************************************************** */

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
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_color;

typedef struct s_textures
{
	mlx_image_t	*sel;
	mlx_image_t	*north;
	mlx_image_t	*south;
	mlx_image_t	*west;
	mlx_image_t	*east;
	t_color		floor;
	t_color		ceiling;
}	t_textures;

typedef struct s_map
{
	char	**map;
	int		x_len;
	int		y_len;
	int		p_y;
	int		p_x;
	
	// textures paths
	char	*north;
	char	*south;
	char	*west;
	char	*east;
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
	int		line_height;
	// 	Textures
	float	wall_x;
	int		tex_x;
	int		tex_y;

}	t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			*map;
	t_player		*pl;
	t_textures		*textures;
	int				res_w;
	int				res_h;
}	t_game;


/* prototypes *************************************************************** */

// parser
//	check_map.c
void	parse_config_line(char *line, t_game *g);
void	check_map(t_game *g);

//	check_path.c
void	check_path_closed(t_map *map);

//	parser_utils.c
int		check_args(t_game *g, int argc, char **argv);
int		parse_file(char *file, t_game	*game);

//	store.c
void	store_map(t_game *g, char **av);


// utils
//	utils.c
void	clear_map(t_map *map);
void	delete_texture_img(t_game *game);
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

//	textures.c
void		load_textures(t_game *g);
mlx_image_t	*select_texture(t_game *g, t_ray *ray);
void	put_tex_pixel(t_game *g, t_ray *ray, int x, int y);


// raycasting
//	raycast.c
void	raycast_loop(t_game *g);

//	dda.c
void	init_dda(t_game *g, t_ray *ray);
void	perform_dda(t_game *g, t_ray *ray);


void	check_vertical(t_game *g, int x, int y);
void	check_horizontal(t_game *g, int x, int y, size_t line_len);
void	check_edges(t_game *g, int x, int y, size_t line_len);
void	check_cell_surroundings(t_game *g, int x, int y);

#endif