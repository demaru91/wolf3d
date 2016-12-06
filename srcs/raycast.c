/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 08:22:50 by sallen            #+#    #+#             */
/*   Updated: 2016/12/06 08:22:52 by sallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

static void		initray(t_env *env, int x)
{
	PLAYER.hcamerad = 2 * x / (double)(WIN_WIDTH) - 1;
	RAY.pos.x = PLAYER.pos.x;
	RAY.pos.y = PLAYER.pos.y;
	RAY.dir.x = PLAYER.dir.x + RAY.plain.x * PLAYER.hcamerad;
	RAY.dir.y = PLAYER.dir.y + RAY.plain.y * PLAYER.hcamerad;
	RAY.posmap.x = (int)RAY.pos.x;
	RAY.posmap.y = (int)RAY.pos.y;
	RAY.disd.x = sqrt(1 + (RAY.dir.y * RAY.dir.y)
			/ (RAY.dir.x * RAY.dir.x));
	RAY.disd.y = sqrt(1 + (RAY.dir.x * RAY.dir.x)
			/ (RAY.dir.y * RAY.dir.y));
	PLAYER.hit = 0;
}

static void		raydir(t_env *env)
{
	if (RAY.dir.x < 0)
	{
		PLAYER.step.x = -1;
		RAY.sidedist.x = (RAY.pos.x - RAY.posmap.x) * RAY.disd.x;
	}
	else
	{
		PLAYER.step.x = 1;
		RAY.sidedist.x = (RAY.posmap.x + 1.0 - RAY.pos.x) * RAY.disd.x;
	}
	if (RAY.dir.y < 0)
	{
		PLAYER.step.y = -1;
		RAY.sidedist.y = (RAY.pos.y - RAY.posmap.y) * RAY.disd.y;
	}
	else
	{
		PLAYER.step.y = 1;
		RAY.sidedist.y = (RAY.posmap.y + 1.0 - RAY.pos.y) * RAY.disd.y;
	}
}

static void		dda(t_env *env)
{
	while (PLAYER.hit == 0)
	{
		if (RAY.sidedist.x < RAY.sidedist.y)
		{
			RAY.sidedist.x += RAY.disd.x;
			RAY.posmap.x += PLAYER.step.x;
			PLAYER.wallside = 0;
		}
		else
		{
			RAY.sidedist.y += RAY.disd.y;
			RAY.posmap.y += PLAYER.step.y;
			PLAYER.wallside = 1;
		}
		if (MAP.map[(int)RAY.posmap.x][(int)RAY.posmap.y] > 0)
			PLAYER.hit = 1;
	}
}

static void		compute(t_env *env)
{
	double	distwall;

	if (PLAYER.wallside == 0)
		distwall = fabs((RAY.posmap.x - RAY.pos.x
					+ (1 - PLAYER.step.x) / 2) / RAY.dir.x);
	else
		distwall = fabs((RAY.posmap.y - RAY.pos.y
				+ (1 - PLAYER.step.y) / 2) / RAY.dir.y);
	RAY.lheight = abs((int)(WIN_HEIGHT / distwall));
	RAY.ystart = (-1 * (RAY.lheight)) / 2 + WIN_HEIGHT / 2;
	if (RAY.ystart < 0)
		RAY.ystart = 0;
	RAY.yend = RAY.lheight / 2 + WIN_HEIGHT / 2;
	if (RAY.yend >= WIN_HEIGHT)
		RAY.yend = WIN_HEIGHT - 1;
}

int				loop_hook(t_env *env)
{
	t_colors	c;
	int			x;

	if (env->img.img != NULL)
	{
		mlx_destroy_image(env->mlx, env->img.img);
		env->img.img = NULL;
	}
	env->img.img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	x = 0;
	while (x < WIN_WIDTH)
	{
		initray(env, x);
		raydir(env);
		dda(env);
		compute(env);
		colors(env, &c);
		drawline(x, env, &c);
		x++;
	}
	get_timeframe(env);
	move(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}
