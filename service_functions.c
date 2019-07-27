/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:21:42 by cyuriko           #+#    #+#             */
/*   Updated: 2019/06/15 20:53:49 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		delete_map(t_map *map)
{
	size_t i;

	i = 0;
	while (i < map->size)
	{
		free(map->data[i]);
		i++;
	}
	free(map->data);
	free(map);
	return (0);
}

void	delete_tets(t_tet *start)
{
	t_tet *temp;

	if (!start)
		return ;
	while (start)
	{
		temp = start->next;
		free(start);
		start = temp;
	}
	return ;
}

size_t	ft_min_sqrt(int num)
{
	int ans;

	ans = 0;
	while (ans * ans < num)
		ans++;
	return (ans);
}

void	remove_figure(int now_pos, t_tet *start, t_map *map)
{
	int x;
	int y;
	int i;
	int j;

	x = now_pos % map->size;
	y = now_pos / map->size;
	i = 0;
	while (i < start->y)
	{
		j = 0;
		while (j < start->x)
		{
			if (map->data[y + i][x + j] == start->index)
				map->data[y + i][x + j] = 0;
			j++;
		}
		i++;
	}
}

void	print_map(t_map *map)
{
	size_t	i;
	size_t	a;
	char	*str;

	i = 0;
	while (i < map->size)
	{
		str = ft_memalloc(sizeof(char) * (map->size + 1));
		ft_memccpy(str, map->data[i], 'z', map->size);
		a = 0;
		while (a < map->size)
		{
			if (!*(str + a))
				*(str + a) = '.';
			a++;
		}
		ft_putstr(str);
		write(1, "\n", 1);
		free(str);
		i++;
	}
}
