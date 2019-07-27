/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:22:16 by cyuriko           #+#    #+#             */
/*   Updated: 2019/06/15 18:58:19 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		can_set_figure(int now_pos, t_tet *start, t_map *map)
{
	int x;
	int y;
	int i;
	int j;
	int ans;

	ans = 1;
	x = now_pos % map->size;
	y = now_pos / map->size;
	i = 0;
	if ((size_t)(x + start->x) > map->size ||
		(size_t)(y + start->y) > map->size)
		return (0);
	while (ans && i < start->y && !(j = 0))
	{
		while (ans && j < start->x)
		{
			if (map->data[y + i][x + j] && ((start->form >>
			(start->x * start->y - 1 - start->x * i - j)) & 1))
				ans = 0;
			j++;
		}
		i++;
	}
	return (ans);
}

void	set_figure(int now_pos, t_tet *start, t_map *map)
{
	int x;
	int y;
	int i;
	int j;

	x = now_pos % map->size;
	y = now_pos / map->size;
	i = 0;
	while (i < start->y && !(j = 0))
	{
		while (j < start->x)
		{
			if (((start->form >>
			(start->x * start->y - 1 - j - start->x * i)) & 1))
				map->data[y + i][x + j] = start->index;
			j++;
		}
		i++;
	}
}

t_map	*create_map(size_t size)
{
	t_map	*map;
	size_t	i;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	if (!(map->data = (char**)malloc((size + 3) * sizeof(char*))))
	{
		free(map);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		if (map && !(map->data[i] = (char*)malloc(size + 1)))
		{
			delete_map(map);
			return (NULL);
		}
		ft_bzero(map->data[i], size + 1);
		i++;
	}
	map->size = size;
	return (map);
}

int		fillit_step(t_tet *start, t_map *map)
{
	int		now_pos;

	if (!start)
		return (1);
	now_pos = 0;
	while ((size_t)now_pos < (map->size * map->size))
	{
		if (can_set_figure(now_pos, start, map))
		{
			set_figure(now_pos, start, map);
			if (fillit_step(start->next, map))
				return (1);
			remove_figure(now_pos, start, map);
		}
		now_pos++;
	}
	return (0);
}

t_map	*fillit(t_tet *start, size_t tet_quantity)
{
	size_t	min_size;
	int		map_not_found;
	t_map	*map;

	map_not_found = 1;
	min_size = ft_min_sqrt(tet_quantity * 4);
	while (map_not_found)
	{
		if (!(map = create_map(min_size)))
		{
			delete_tets(start);
			return (NULL);
		}
		if (fillit_step(start, map))
			map_not_found = 0;
		else
		{
			delete_map(map);
			min_size++;
		}
	}
	return (map);
}
