/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:04:50 by mailinci          #+#    #+#             */
/*   Updated: 2024/10/21 22:23:10 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_mlx	game_init(char *map_file)
{
	t_mlx	game;

	game.map = create_map(map_file);
	game.window = NULL;
	game.collectible = 0;
	game.collectible_count = 1;
	game.moves = 0;
	game.poopie.x = 0;
	game.poopie.y = 0;
	game.img.tiles = NULL;
	game.img.wall = NULL;
	game.img.paper = NULL;
	game.img.toilet[0] = NULL;
	game.img.toilet[1] = NULL;
	game.img.poopie = NULL;
	game.map_dimensions.width = 0;
	game.map_dimensions.height = 0;
	return (game);
}

int	esc(int keycode, t_mlx *game)
{
	if (keycode == ESC && game->data != NULL)
	{
		end(game);
	}
	return (0);
}

void	destroy_image(t_mlx *game)
{
	if (game->img.paper)
		mlx_destroy_image(game->data, game->img.paper);
	if (game->img.poopie)
		mlx_destroy_image(game->data, game->img.poopie);
	if (game->img.tiles)
		mlx_destroy_image(game->data, game->img.tiles);
	if (game->img.toilet[0])
		mlx_destroy_image(game->data, game->img.toilet[0]);
	if (game->img.toilet[1])
		mlx_destroy_image(game->data, game->img.toilet[1]);
	if (game->img.wall)
		mlx_destroy_image(game->data, game->img.wall);
}

void	set_poopie_position(t_mlx *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[j])
	{
		i = 0;
		while (game->map[j][i])
		{
			if (game->map[j][i] == 'P')
			{
				game->poopie.x = i;
				game->poopie.y = j;
				return ;
			}
			i++;
		}
		j++;
	}
}

int	collectible_count(t_mlx *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->collectible_count = 0;
	while (game->map[j])
	{
		i = 0;
		while (game->map[j][i])
		{
			if (game->map[j][i] == 'C')
			{
				game->collectible_count++;
			}
			i++;
		}
		j++;
	}
	return (game->collectible_count);
}
