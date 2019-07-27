/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 15:56:46 by cyuriko           #+#    #+#             */
/*   Updated: 2019/06/15 19:08:01 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tet	*read_task(int fd)
{
	t_tet	*all_data;
	int		read_info;
	char	*read_data;

	all_data = NULL;
	while (1)
	{
		if (!get_tet(fd, &all_data))
		{
			delete_tets(all_data);
			return (NULL);
		}
		read_data = NULL;
		if ((read_info = get_next_line(fd, &read_data)) && *read_data == '\0')
		{
			free(read_data);
			continue;
		}
		if (read_info == 0)
			break ;
		delete_tets(all_data);
		return (NULL);
	}
	return (all_data);
}

int		count_tet_size(t_tet *start)
{
	int ans;

	ans = 0;
	while (start)
	{
		ans++;
		start = start->next;
	}
	return (ans);
}

int		put_error(char *str)
{
	ft_putstr(str);
	return (0);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_tet	*data;
	t_map	*answer;

	if (argc != 2)
		return (put_error("usage: ./fillit correct_file\n"));
	fd = open(argv[1], O_RDONLY);
	data = read_task(fd);
	if (!data)
		return (put_error("error\n"));
	if (count_tet_size(data) > 26 ||
	!(answer = fillit(data, count_tet_size(data))))
		put_error("error\n");
	else
	{
		print_map(answer);
		delete_map(answer);
	}
	delete_tets(data);
	close(fd);
	return (0);
}
