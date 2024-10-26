/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:36:45 by mailinci          #+#    #+#             */
/*   Updated: 2024/10/26 14:18:24 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game	setup_game(char *map_file, t_dimensions *d)
{
	t_game	game;

	*d = get_map_dimensions(map_file);
	game.map = create_map(map_file);
	return (game);
}

int	check_map_objects(char *map_file)
{
	t_objects	object;

	set_objects(&object);
	object.fd = open(map_file, O_RDONLY);
	object.line = ft_get_next_line(object.fd);
	while (object.line != NULL)
	{
		count_objects_in_line(object.line, &object);
		free(object.line);
		object.line = ft_get_next_line(object.fd);
	}
	close(object.fd);
	if (object.poopie == 1 && object.exit == 1 && object.collectible >= 1)
		return (0);
	else
		return (1);
}

int	parse(int argc, char *argv[])
{
	if (check_usage_and_file_type(argc, argv[1]))
		return (1);
	if (validate_map_file(argv[1]))
		return (1);
	if (!is_playable(argv[1]))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	game;

	if (parse(argc, argv))
		return (1);
	game = game_init(argv[1]);
	if (game_start(game))
		return (1);
	return (0);
}
