/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 08:22:59 by sallen            #+#    #+#             */
/*   Updated: 2016/12/06 08:23:01 by sallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int		ft_esc(t_env *env)
{
	int i;

	mlx_clear_window(env->mlx, env->win);
	mlx_destroy_image(env->mlx, env->img.img);
	mlx_destroy_window(env->mlx, env->win);
	i = -1;
	while (env->map.map[++i] != NULL)
		free(env->map.map[i]);
	free(env->map.map);
	exit(0);
}

void	get_timeframe(t_env *env)
{
	struct timeval	time;

	env->oldtime = env->time;
	gettimeofday(&time, NULL);
	env->time = time.tv_sec * 1000 + time.tv_usec / 1000;
	env->frametime = env->time - env->oldtime;
	PLAYER.mspeed = env->frametime * 0.003;
	PLAYER.rspeed = env->frametime * 0.005;
}

int		size_word(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	put_int_in_tab(int nb_w, char c, int *tab, char *s)
{
	int		i;
	int		j;
	int		size;

	size = 0;
	i = 0;
	j = 0;
	while (s[i] != '\0' && j < nb_w)
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1] != '\0') ||
				(s[0] != c && i == 0))
		{
			if (s[i] == c)
				i++;
			size = size_word(&s[i], c);
			tab[j] = ft_atoi(ft_strsub(s, i, size));
			j++;
		}
		i++;
	}
}

int		*ft_strsplittoint(char const *s, char c)
{
	int		*tab;
	int		nb_w;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	nb_w = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1] != '\0') ||
				(s[0] != c && i == 0))
			nb_w++;
		i++;
	}
	tab = (int *)malloc(sizeof(int) * nb_w);
	if (tab)
		put_int_in_tab(nb_w, c, tab, (char*)s);
	else
		return (NULL);
	return (tab);
}
