/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/17 02:25:25 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

int	check_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		ft_error("Error\nUsage: ./cub3D <map.cub>\n", NULL, NULL);
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strcmp(argv[1] + len - 4, ".cub") != 0)
		ft_error("Error\nFile must have .cub extension\n", NULL, NULL);
	return (1);
}

int	parse_file(char *file, t_game	*game)
{
	int		fd;
	char	*line;

	(void) game;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open file: %s\n", file);
		return (0);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
