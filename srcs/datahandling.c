/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datahandling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 08:22:28 by sallen            #+#    #+#             */
/*   Updated: 2016/12/06 08:22:30 by sallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	readsize(t_env *env, int fd)
{
	int		*size;
	char	*line;

	if (get_next_line(fd, &line) < 1)
	{
		perror("Could not read map size!!!");
		exit(EXIT_FAILURE);
	}
	size = ft_strsplittoint(line, ' ');
	MAP.sizex = size[0];
	MAP.sizey = size[1];
	free(size);
	free(line);
}

void	readmap(t_env *env, int fd)
{
	char	*line;
	int		**worldmap;
	int		i;

	i = 0;
	worldmap = (int **)malloc(sizeof(int *) * MAP.sizex);
	if (worldmap == NULL)
	{
		perror("Could not read map!!!");
		exit(EXIT_FAILURE);
	}
	while (get_next_line(fd, &line) > 0)
	{
		worldmap[i] = ft_strsplittoint(line, ' ');
		i++;
		free(line);
	}
	MAP.map = worldmap;
}

void	readfile(t_env *env, char *input)
{
	int		fd;
	int		i;

	i = 0;
	if ((fd = open(input, O_RDONLY)) == -1)
	{
		perror("Map missing!!!");
		exit(EXIT_FAILURE);
	}
	readsize(env, fd);
	readmap(env, fd);
	close(fd);
}
