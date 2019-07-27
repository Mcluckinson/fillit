/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_works.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 19:43:14 by cyuriko           #+#    #+#             */
/*   Updated: 2019/06/15 18:58:19 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tet			*malloc_tet(void)
{
	t_tet *new;

	if (!(new = (t_tet*)malloc(sizeof(t_tet))))
		return (NULL);
	new->form = 0;
	new->x = 0;
	new->y = 0;
	new->next = 0;
	new->index = 0;
	return (new);
}

t_tet			*add_malloc_tet(t_tet **answer)
{
	t_tet *now;
	t_tet *new;

	if (!*answer)
	{
		*answer = malloc_tet();
		(*answer)->index = 'A';
		return (*answer);
	}
	now = *answer;
	while (now->next)
		now = now->next;
	new = malloc_tet();
	now->next = new;
	new->index = now->index + 1;
	return (new);
}

t_input_tet		*new_input(void)
{
	t_input_tet	*new;

	if (!(new = (t_input_tet*)malloc(sizeof(t_input_tet))))
		return (NULL);
	new->x_finish = 3;
	new->x_start = 0;
	new->y_finish = 3;
	new->y_start = 0;
	if (!(new->data = (char**)malloc(4 * sizeof(char*))))
	{
		free(new);
		return (NULL);
	}
	ft_bzero(new->data, sizeof(char*) * 4);
	return (new);
}

int				dell_input(t_input_tet *input)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (input->data[i])
			free(input->data[i]);
		input->data[i] = 0;
		i++;
	}
	free(input->data);
	free(input);
	return (0);
}

int				check_neighbour(t_input_tet *input, int x, int y)
{
	int connections;

	connections = 0;
	if (y < 4 && input->data[x][y + 1] == '#')
		connections++;
	if (y > 0 && input->data[x][y - 1] == '#')
		connections++;
	if (x > 0 && input->data[x - 1][y] == '#')
		connections++;
	if (x < 3 && input->data[x + 1][y] == '#')
		connections++;
	return (connections);
}
