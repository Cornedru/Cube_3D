/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/30 00:04:28 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cube.h"

static void count_spawn_and_validate_chars(t_game *g)
{
    int     spawn_count;
    char    c;
    int     x;
    int     y;

    spawn_count = 0;
    y = -1;
    while (++y < g->map->y_len)
    {
        x = 0;
        while (g->map->map[y][x])
        {
            c = g->map->map[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                spawn_count++;
                init_player_data(g, x, y, c);
            }
            else if (c != '0' && c != '1' && c != ' ')
                ft_error("Invalid character in map", g->map, NULL);
            x++;
        }
    }
    if (spawn_count != 1)
        ft_error("Map must have exactly 1 spawn point (N/S/E/W)", g->map, NULL);
}

static void parse_color(char *line, t_color *color)
{
    char    **rgb;

    rgb = ft_split(line, ',');
    if (!rgb || ft_arraylen(rgb) != 3)
        ft_error("Invalid RGB format", NULL, NULL);
    color->r = ft_atoi(rgb[0]);
    color->g = ft_atoi(rgb[1]);
    color->b = ft_atoi(rgb[2]);
    if (color->r < 0 || color->r > 255
        || color->g < 0 || color->g > 255
        || color->b < 0 || color->b > 255)
        ft_error("RGB values must be between 0 and 255", NULL, NULL);
    gc_free_array((void **)rgb);
}

void    parse_config_line(char *line, t_game *g)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
        g->map->north = ft_strtrim(ft_strdup(line + 3), "\n");
    else if (ft_strncmp(line, "SO ", 3) == 0)
        g->map->south = ft_strtrim(ft_strdup(line + 3), "\n");
    else if (ft_strncmp(line, "WE ", 3) == 0)
        g->map->west = ft_strtrim(ft_strdup(line + 3), "\n");
    else if (ft_strncmp(line, "EA ", 3) == 0)
        g->map->east = ft_strtrim(ft_strdup(line + 3), "\n");
    else if (ft_strncmp(line, "F ", 2) == 0)
        parse_color(line + 2, &g->textures->floor);
    else if (ft_strncmp(line, "C ", 2) == 0)
        parse_color(line + 2, &g->textures->ceiling);
    else
        ft_error("Invalid config line", NULL, NULL);
}

static void calculate_map_dimensions(t_map *map)
{
    int     i;
    size_t  len;
    size_t  max_len;

    max_len = 0;
    i = 0;
    while (i < map->y_len)
    {
        len = ft_strlen(map->map[i]);
        if (len > max_len)
            max_len = len;
        i++;
    }
    map->x_len = max_len;
}

static void check_cell_surroundings(t_game *g, int x, int y)
{
    size_t  line_len;
    char    c;
    
    c = g->map->map[y][x];
    
    if (c == '1' || c == ' ')
        return;
    line_len = ft_strlen(g->map->map[y]);
    if (y == 0 || y == g->map->y_len - 1)
        ft_error("Map must be surrounded by walls (top/bottom edge)", g->map, NULL);
    if (x == 0 || x == (int)line_len - 1)
        ft_error("Map must be surrounded by walls (left/right edge)", g->map, NULL);
    if (y > 0)
    {
        if (x >= (int)ft_strlen(g->map->map[y - 1]) || g->map->map[y - 1][x] == ' ')
            ft_error("Map not closed: space above playable area in y - 1", g->map, NULL);
    }
    if (y < g->map->y_len - 1)
    {
        if (x >= (int)ft_strlen(g->map->map[y + 1]) || g->map->map[y + 1][x] == ' ')
            ft_error("Map not closed: space below playable area in y + 1", g->map, NULL);
    }
    if (x > 0 && g->map->map[y][x - 1] == ' ')
        ft_error("Map not closed: space left of playable area - 1", g->map, NULL);
    if (x < (int)line_len - 1 && g->map->map[y][x + 1] == ' ')
        ft_error("Map not closed: space right of playable area + 1", g->map, NULL);
}

static void validate_map_borders(t_game *g)
{
    int x;
    int y;
    
    y = 0;
    while (y < g->map->y_len)
    {
        x = 0;
        while (g->map->map[y][x])
        {
            if (g->map->map[y][x] == '0' || 
                g->map->map[y][x] == 'N' || 
                g->map->map[y][x] == 'S' || 
                g->map->map[y][x] == 'E' || 
                g->map->map[y][x] == 'W')
            {
                check_cell_surroundings(g, x, y);
            }
            x++;
        }
        y++;
    }
}

void    check_map(t_game *g)
{
    if (!g->map || !g->map->map || !(*g->map->map))
        ft_error("Map not loaded", g->map, NULL);
    g->map->y_len = 0;
    while (g->map->map[g->map->y_len])
        g->map->y_len++;
    calculate_map_dimensions(g->map);
    count_spawn_and_validate_chars(g);
    validate_map_borders(g);
}