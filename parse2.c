/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:36:45 by mailinci          #+#    #+#             */
/*   Updated: 2024/10/26 14:01:29 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_walls(t_game game, t_dimensions d)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < d.height)
	{
		j = 0;
		while (j < d.width)
		{
			if (i == 0 || i == d.height - 1 || j == 0 || j == d.width - 1)
			{
				if (game.map[i][j] != '1')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	**map_copy(char **map)
{
	char	**map_cpy;
	int		len;
	int		i;

	i = 0;
	len = count_rows(map);
	map_cpy = ft_calloc(sizeof(char *), len + 1);
	if (!map_cpy)
		return (NULL);
	while (i < len && map[i])
	{
		map_cpy[i] = ft_strdup(map[i]);
		if (!map_cpy[i])
			return (free_map(map_cpy), NULL);
		i++;
	}
	map_cpy[i] = NULL;
	return (map_cpy);
}

bool	is_it_filled(t_parsing *check)
{
	int	y;
	int	x;

	y = 0;
	while (check->map[y] != NULL)
	{
		x = 0;
		while (check->map[y][x] != '\0')
		{
			if (check->map[y][x] == 'E')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

t_coord	player_position(char **map)
{
	t_coord	c;
	int		i;
	int		j;

	c.x = -1;
	c.y = -1;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'P')
			{
				c.x = j;
				c.y = i;
				return (c);
			}
			j++;
		}
		i++;
	}
	return (c);
}

int	check_collectibles(char **map, t_dimensions d)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < d.height)
	{
		j = 0;
		while (j < d.width)
		{
			if (map[i][j] == 'C')
			{
				ft_printf("Error: Unplayable map2\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
