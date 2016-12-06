/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 08:23:07 by sallen            #+#    #+#             */
/*   Updated: 2016/12/06 08:23:09 by sallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	init_mlx(t_env *env)
{
	env->mlx = mlx_init();
	if ((env->mlx = mlx_init()) == NULL)
		exit(EXIT_FAILURE);
	WIN = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "Wolf3d");
	IMG.img = NULL;
	PLAYER.pos.x = 4;
	PLAYER.pos.y = 4;
	PLAYER.dir.x = -1;
	PLAYER.dir.y = 0;
	RAY.plain.x = 0;
	RAY.plain.y = 0.80;
	env->time = 0;
	env->oldtime = 0;
}

int		main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
	{
		ft_putendl("Insert 1 map as parameter!");
		exit(0);
	}
	init_mlx(&env);
	readfile(&env, argv[1]);
	mlx_loop_hook(env.mlx, &loop_hook, &env);
	mlx_hook(env.win, 2, (1L << 0), &key_press, &env);
	mlx_hook(env.win, 3, (1L << 1), &key_release, &env);
	mlx_hook(env.win, 17, 0L, ft_esc, &env);
	mlx_loop(env.mlx);
	return (0);
}
