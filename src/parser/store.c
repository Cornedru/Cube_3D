/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/20 15:13:47 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	add_map_to_struct(char **argv, t_map *map)
{
	int		i;
	int		j;
	int		fd;
	char	*gnl;

	i = 0;
	map->map[i] = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_error("File does not exist!", map, NULL);
	gnl = get_next_line(fd);
	if (!gnl)
		return (close(fd), ft_error("File empty!", map, NULL));
	while (gnl)
	{
		j = 0;
		while (gnl[j] && gnl[j] != '\n')
			j++;
		if (gnl[j] == '\n')
			gnl[j] = '\0';
		map->map[i++] = gnl;
		gnl = get_next_line(fd);
	}
	map->map[i] = NULL;
	close(fd);
}

void	store_map(t_map *map, char **av)
{
	int		fd;
	char	*gnl;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_error("files does not exist", map, NULL);
	gnl = get_next_line(fd);
	if (!gnl)
		return (close(fd), ft_error("File empty", map, NULL));
	while (gnl)
	{
		map->y_len++;
		free(gnl);
		gnl = get_next_line(fd);
	}
	close(fd);
	map->map = malloc(sizeof(char *) * (map->y_len + 1));
	if (!map->map)
		ft_error("Memory allocation failed", map, NULL);
	add_map_to_struct(av, map);
}
