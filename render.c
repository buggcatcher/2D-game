/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:48:46 by mailinci          #+#    #+#             */
/*   Updated: 2024/10/26 15:29:44 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
}

void	image_select(t_mlx *window, char c, int x, int y)
{
	if (c == '0')
		mlx_put_image_to_window(window->data, window->window, \
		window->img.tiles, x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (c == '1')
		mlx_put_image_to_window(window->data, window->window, \
		window->img.wall, x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (c == 'C')
		mlx_put_image_to_window(window->data, window->window, \
		window->img.paper, x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (c == 'E' && window->collectible_count != 0)
		mlx_put_image_to_window(window->data, window->window, \
		window->img.toilet[0], x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (c == 'E' && window->collectible_count == 0)
		mlx_put_image_to_window(window->data, window->window, \
		window->img.toilet[1], x * IMG_WIDTH, y * IMG_HEIGHT);
	else if (c == 'P')
		mlx_put_image_to_window(window->data, window->window, \
		window->img.poopie, x * IMG_WIDTH, y * IMG_HEIGHT);
}

void	put_image(t_mlx *window)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (window->map[j])
	{
		while (window->map[j][i])
		{
			image_select(window, window->map[j][i], i, j);
			i++;
		}
		i = 0;
		j++;
	}
}

void	render(t_mlx *mlx)
{
	int	w;
	int	h;

	w = IMG_WIDTH;
	h = IMG_HEIGHT;
	mlx->img.tiles = mlx_xpm_file_to_image(mlx->data, \
	"textures/tiles.xpm", &w, &h);
	mlx->img.wall = mlx_xpm_file_to_image(mlx->data, \
	"textures/wall.xpm", &w, &h);
	mlx->img.paper = mlx_xpm_file_to_image(mlx->data, \
	"textures/paper.xpm", &w, &h);
	mlx->img.toilet[0] = mlx_xpm_file_to_image(mlx->data, \
	"textures/toilet_closed.xpm", &w, &h);
	mlx->img.toilet[1] = mlx_xpm_file_to_image(mlx->data, \
	"textures/toilet_open.xpm", &w, &h);
	mlx->img.poopie = mlx_xpm_file_to_image(mlx->data, \
	"textures/poopie.xpm", &w, &h);
}

int	end(t_mlx *game)
{
	if (game->map)
		free_map(game->map);
	destroy_image(game);
	mlx_clear_window(game->data, game->window);
	if (game->window)
		mlx_destroy_window(game->data, game->window);
	if (game->data)
		mlx_destroy_display(game->data);
	free(game->data);
	game->data = NULL;
	game->map = NULL;
	exit(0);
}
