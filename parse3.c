/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:17:21 by mailinci          #+#    #+#             */
/*   Updated: 2024/10/26 14:11:13 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	perform_playability_checks(t_game game, t_dimensions d)
{
	t_coord		c;
	t_parsing	check;
	char		**map_dup;

	map_dup = map_copy(game.map);
	if (!map_dup)
		return (0);
	check = set_dimentions(map_dup, d);
	c = player_position(game.map);
	flood_fill(c.x, c.y, &check);
	if (!is_it_filled(&check))
	{
		print_map(check.map);
		free_map(map_dup);
		return (write(1, "Error: Unplayable map1\n", 24), 0);
	}
	if (check_collectibles(check.map, d))
	{
		free_map(check.map);
		free_map(game.map);
		exit(1);
	}
	free_map(map_dup);
	return (1);
}

int	check_playability(t_game game, t_dimensions d)
{
	int	result;

	if (check_map_walls(game, d))
	{
		free_map(game.map);
		return (write(1, "Error: Invalid map\n", 20), 0);
	}
	result = perform_playability_checks(game, d);
	free_map(game.map);
	return (result);
}

int	char_check(char **map, t_dimensions d)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < d.height)
	{
		j = 0;
		while (j < d.width)
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'P' && \
			map[i][j] != 'E' && map[i][j] != 'C')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	is_playable(char *map_file)
{
	t_game			game;
	t_dimensions	d;

	game = setup_game(map_file, &d);
	if (!game.map)
		return (0);
	if (char_check(game.map, d))
	{
		ft_printf("Error: Invalid map\n");
		return (0);
	}
	return (check_playability(game, d));
}

void	count_objects_in_line(char *line, t_objects *object)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == POOPIE)
			object->poopie++;
		else if (line[i] == EXIT)
			object->exit++;
		else if (line[i] == COLLECTABLE)
			object->collectible++;
		i++;
	}
}
