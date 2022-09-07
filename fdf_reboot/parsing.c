/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:10:57 by tlafay            #+#    #+#             */
/*   Updated: 2022/01/14 14:30:15 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	**join_2d_2(char *str)
{
	char	**ret;

	ret = (char **)malloc(2 * sizeof(char *));
	ret[0] = str;
	ret[1] = NULL;
	return (ret);
}

char	**strjoin_2d(char **tab, char *str, int *stop)
{
	char	**ret;
	int		i;

	if (!tab)
		return (join_2d_2(str));
	if (!str)
	{
		*stop = 1;
		return (tab);
	}
	i = 0;
	while (tab[i])
		i++;
	ret = (char **)malloc((i + 2) * sizeof(char *));
	i = 0;
	while (tab[i])
	{
		ret[i] = ft_strdup(tab[i]);
		free(tab[i]);
		i++;
	}
	ret[i] = str;
	ret[i + 1] = NULL;
	free(tab);
	return (ret);
}

char	**read_map(char *filename)
{
	char	**tmp;
	int		i;
	int		fd;
	int		stop;

	i = 0;
	stop = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	tmp = NULL;
	while (1)
	{
		tmp = strjoin_2d(tmp, get_next_line(fd), &stop);
		if (stop == 1)
			break ;
	}
	close(fd);
	return (tmp);
}

t_point	*parse_map(char **map, int *width)
{
	int		x;
	int		y;
	int		i;
	char	**split;
	t_point	*ret;

	i = 0;
	y = -1;
	ret = (t_point *)malloc((HEIGHT * WIDTH + 1) * sizeof(t_point));
	while (map[++y])
	{
		x = -1;
		split = ft_split(map[y], ' ');
		while (split[++x + 1])
		{
			init_point(&ret[i], x, y, ft_atoi(split[x]));
			free(split[x]);
			i++;
		}
		free(split[x]);
		free(split);
		*width = x;
	}
	ret[i].exists = 0;
	return (ret);
}

t_system	get_map(char *filename, t_system system)
{
	t_system	ret;
	char		**map;
	int			i;

	map = read_map(filename);
	i = 0;
	while (map[i])
		i++;
	ret.height = i;
	ret.map = parse_map(map, &ret.width);
	ret.i = system.i;
	ret.j = system.j;
	ret.k = system.k;
	ret.ref = system.ref;
	ret.norm = system.norm;
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	return (ret);
}
