/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:23:12 by mailinci          #+#    #+#             */
/*   Updated: 2024/10/26 14:16:19 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_dimensions	get_map_dimensions(char *map_file)
{
	t_dimensions	d;
	int				fd;
	char			*line;

	d.height = 0;
	d.width = 0;
	fd = open(map_file, O_RDONLY);
	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		if (d.height == 0)
		{
			d.width = ft_strlen(line);
			if (line[d.width - 1] == '\n')
				d.width--;
		}
		d.height++;
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	return (d);
}

t_game	allocate_map_memory(t_dimensions d)
{
	t_game	game;
	size_t	i;

	game.map = (char **)ft_calloc(sizeof(char *), d.height + 1);
	i = 0;
	while (i < d.height)
	{
		game.map[i] = (char *)ft_calloc(sizeof(char), d.width + 1);
		i++;
	}
	return (game);
}

void	fill_map(t_game game, t_dimensions d, int fd)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	while (i < d.height)
	{
		line = ft_get_next_line(fd);
		if (!line)
		{
			while (i > 0)
			{
				i--;
				free(game.map[i]);
			}
		}
		j = 0;
		while (j < d.width)
		{
			game.map[i][j] = line[j];
			j++;
		}
		game.map[i++][d.width] = '\0';
		free(line);
	}
}

char	**create_map(char *map_file)
{
	t_dimensions	d;
	t_game			game;
	int				fd;

	d = get_map_dimensions(map_file);
	fd = open(map_file, O_RDONLY);
	game = allocate_map_memory(d);
	if (!game.map)
		return (0);
	fill_map(game, d, fd);
	if (!&fill_map)
	{
		free_map(game.map);
		return (0);
	}
	close(fd);
	return (game.map);
}
