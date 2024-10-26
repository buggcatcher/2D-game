/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:32:38 by mailinci          #+#    #+#             */
/*   Updated: 2024/10/18 14:38:57 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_move(t_mlx *game, int new_x, int new_y)
{
	char	object;

	if (new_x < 0 || new_y < 0 || new_x >= (int)game->map_dimensions.width \
	|| new_y >= (int)game->map_dimensions.height)
		return (1);
	if (!game->map)
		return (1);
	object = game->map[new_y][new_x];
	if (object == WALL)
		return (1);
	if (object == EXIT && game->collectible_count != 0)
		return (1);
	if (object == EXIT && game->collectible_count == 0)
		end(game);
	if (object == COLLECTABLE)
	{
		game->map[new_y][new_x] = EMPTY;
	}
	return (0);
}

int	move(t_mlx *game, int x_offset, int y_offset)
{
	int	new_x;
	int	new_y;
	int	toilet_papers_remaining;

	new_x = game->poopie.x + x_offset;
	new_y = game->poopie.y + y_offset;
	if (!game || !game->map)
		return (1);
	if (check_move(game, new_x, new_y))
		return (1);
	game->map[new_y][new_x] = POOPIE;
	game->map[game->poopie.y][game->poopie.x] = EMPTY;
	game->poopie.x = new_x;
	game->poopie.y = new_y;
	game->moves++;
	print_map(game->map);
	ft_printf("Moves:\t\t%d\n", game->moves);
	ft_printf("Mr. Poopie xy:\t%d, %d\n", new_x, new_y);
	toilet_papers_remaining = collectible_count(game);
	ft_printf("Toilet papers:\t%d\n\n", toilet_papers_remaining);
	put_image(game);
	return (0);
}

int	move_poopie(int keycode, t_mlx *game)
{
	int	x_offset;
	int	y_offset;

	x_offset = 0;
	y_offset = 0;
	if (!game || !game->data)
		return (1);
	if (keycode == ESC)
	{
		end(game);
		return (0);
	}
	if (keycode == XK_w)
		y_offset = -1;
	else if (keycode == XK_a)
		x_offset = -1;
	else if (keycode == XK_s)
		y_offset = 1;
	else if (keycode == XK_d)
		x_offset = 1;
	else
		return (1);
	return (move(game, x_offset, y_offset));
}

int	game_start(t_mlx game)
{
	game.data = mlx_init();
	if (!game.data)
	{
		end(&game);
		return (1);
	}
	game.window = mlx_new_window(game.data,
			ft_strlen(game.map[0]) * IMG_WIDTH,
			count_rows(game.map) * IMG_HEIGHT,
			"Toilet Run");
	game.map_dimensions.width = ft_strlen(game.map[0]);
	game.map_dimensions.height = count_rows(game.map);
	render(&game);
	put_image(&game);
	set_poopie_position(&game);
	mlx_hook(game.window, DestroyNotify, NoEventMask, end, &game);
	mlx_hook(game.window, KeyPress, KeyPressMask, move_poopie, &game);
	if (game.data)
		mlx_loop(game.data);
	return (0);
}
