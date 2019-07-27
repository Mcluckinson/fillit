/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:47:09 by cyuriko           #+#    #+#             */
/*   Updated: 2019/06/15 18:58:19 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct		s_tet
{
	int				form;
	int				x;
	int				y;
	struct s_tet	*next;
	char			index;
}					t_tet;

typedef struct		s_input_tet
{
	char	**data;
	int		x_start;
	int		y_start;
	int		x_finish;
	int		y_finish;
}					t_input_tet;

typedef struct		s_map
{
	char	**data;
	size_t	size;
}					t_map;

t_input_tet			*new_input(void);
int					dell_input(t_input_tet *input);
int					check_add(char *string, t_input_tet *input, int str_num);
void				find_corner(t_input_tet *input);
int					check_tet(t_input_tet *input);
t_tet				*malloc_tet(void);
t_tet				*add_malloc_tet(t_tet **answer);
int					add_to_tet(t_input_tet *input, t_tet **answer);
int					get_tet(int fd, t_tet **answer);
int					check_neighbour(t_input_tet *input, int x, int y);
int					can_set_figure(int now_pos, t_tet *start, t_map *map);
void				set_figure(int now_pos, t_tet *start, t_map *map);
void				remove_figure(int now_pos, t_tet *start, t_map *map);
t_map				*create_map(size_t size);
size_t				ft_min_sqrt(int num);
int					fillit_step(t_tet *start, t_map *map);
t_map				*fillit(t_tet *start, size_t tet_quantity);
int					delete_map(t_map *map);
void				delete_tets(t_tet *start);
void				print_map(t_map *map);

#endif
