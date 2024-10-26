/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:32:27 by mailinci          #+#    #+#             */
/*   Updated: 2024/10/26 14:18:46 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include "libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/keysymdef.h>

# define IMG_WIDTH 128
# define IMG_HEIGHT 128
# define ESC 65307
# define WALL '1'
# define EXIT 'E'
# define COLLECTABLE 'C'
# define POOPIE 'P'
# define EMPTY '0'

typedef struct s_game
{
	char	**map;
}	t_game;

typedef struct s_coord
{
	int		x;
	int		y;
}	t_coord;

typedef struct dimensions
{
	size_t	width;
	size_t	height;
}	t_dimensions;

typedef struct s_objects
{
	int		poopie;
	int		collectible;
	int		exit;
	char	*line;
	int		fd;

}	t_objects;

typedef struct s_parsing
{
	char	**map;
	int		width;
	int		height;	
	int		exit_found;
}	t_parsing;

typedef struct s_img
{
	void	*toilet[2];
	void	*wall;
	void	*paper;
	void	*tiles;
	void	*poopie;
}	t_img;

typedef struct s_mlx
{
	void			*data;
	void			*window;
	char			**map;
	int				collectible;
	int				collectible_count;
	int				moves;
	t_coord			poopie;
	t_img			img;
	t_dimensions	map_dimensions;
}	t_mlx;

int				check_usage_and_file_type(int argc, char *map_file);
int				validate_map_file(char *map_file);
void			set_objects(t_objects *obj);
char			**create_map(char *map_file);
char			**map_copy(char **map);
int				is_playable(char *map_file);
int				count_rows(char **map);
void			flood_fill(int x, int y, t_parsing *check);
void			free_map(char **map);
t_dimensions	get_map_dimensions(char *map_file);
t_parsing		set_dimentions(char **map_copy, t_dimensions d);
int				game_start(t_mlx game);
int				is_playable(char *map_file);
int				check_map_walls(t_game game, t_dimensions d);
t_coord			player_position(char **map);
bool			is_it_filled(t_parsing *check);
void			render(t_mlx *mlx);
t_mlx			game_init(char *map_file);
int				end(t_mlx *game);
int				check_map_line_lengths(int fd);
int				validate_line_lengths(int fd, size_t line_length);
int				esc(int keycode, t_mlx *game);
void			put_image(t_mlx *window);
int				move_poopie(int keycode, t_mlx *game);
void			image_select(t_mlx *window, char c, int x, int y);
void			set_poopie_position(t_mlx *game);
int				check_collectibles(char **map, t_dimensions d);
int				collectible_count(t_mlx *game);
void			destroy_image(t_mlx *game);
void			count_objects_in_line(char *line, t_objects *object);
void			print_map(char **map);
t_game			setup_game(char *map_file, t_dimensions *d);
int				check_map_objects(char *map_file);

#endif