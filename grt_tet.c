/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grt_tet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 19:45:25 by cyuriko           #+#    #+#             */
/*   Updated: 2019/06/15 18:58:19 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		check_add(char *string, t_input_tet *input, int str_num)
{
	int i;

	i = 0;
	if (!string)
		return (0);
	if (ft_strlen(string) != 4)
	{
		free(string);
		return (0);
	}
	while (i < 4)
	{
		if (string[i] != '.' && string[i] != '#')
		{
			free(string);
			return (0);
		}
		i++;
	}
	input->data[str_num] = string;
	return (1);
}

void	find_corner(t_input_tet *input)
{
	int now_min_start;
	int now_min_finish;
	int i;

	now_min_start = 5;
	now_min_finish = 0;
	while (!ft_strchr(input->data[input->y_start], '#'))
		input->y_start++;
	while (!ft_strchr(input->data[input->y_finish], '#'))
		input->y_finish--;
	i = input->y_start;
	while (i <= input->y_finish)
	{
		now_min_start = ft_min(now_min_start,
				ft_strchr(input->data[i], '#') - input->data[i]);
		now_min_finish = ft_max(now_min_finish,
				(ft_strrchr(input->data[i], '#') - input->data[i]));
		i++;
	}
	input->x_finish = now_min_finish;
	input->x_start = now_min_start;
}

int		check_tet(t_input_tet *input)
{
	int x;
	int y;
	int num_fiill;
	int connections;

	x = 0;
	num_fiill = 0;
	connections = 0;
	while (x < 4 && !(y = 0))
	{
		while (y < 4)
		{
			if (input->data[x][y] == '#')
			{
				num_fiill++;
				if (!check_neighbour(input, x, y))
					return (0);
				connections = connections || (check_neighbour(input, x, y) - 1);
			}
			y++;
		}
		x++;
	}
	return (!(num_fiill != 4 || !connections));
}

int		add_to_tet(t_input_tet *input, t_tet **answer)
{
	int		x;
	int		y;
	t_tet	*now_tet;

	if (!check_tet(input) || !(now_tet = add_malloc_tet(answer)))
		return (0);
	find_corner(input);
	y = input->y_start;
	while (y <= input->y_finish)
	{
		x = input->x_start;
		while (x <= input->x_finish)
			now_tet->form = ((now_tet->form) << 1)
					+ (input->data[y][x++] == '#');
		y++;
	}
	now_tet->x = input->x_finish - input->x_start + 1;
	now_tet->y = input->y_finish - input->y_start + 1;
	dell_input(input);
	return (1);
}

int		get_tet(int fd, t_tet **answer)
{
	char		*string;
	int			i;
	int			read_info;
	t_input_tet	*input;

	string = 0;
	if (!(input = new_input()))
		return (0);
	i = 0;
	while (i++ < 4 && (read_info = get_next_line(fd, &string)))
	{
		if (!read_info && i != 4)
			return (dell_input(input));
		if (read_info < 1 || !check_add(string, input, i - 1))
			return (dell_input(input));
	}
	if (i < 5 || read_info == 0)
		return (dell_input(input));
	return (add_to_tet(input, answer));
}
