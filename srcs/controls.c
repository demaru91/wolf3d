/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 08:22:19 by sallen            #+#    #+#             */
/*   Updated: 2016/12/06 08:22:22 by sallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int		key_press(int keycode, t_env *env)
{
	if LEFT
		PLAYER.move.left = 1;
	if FORWARD
		PLAYER.move.up = 1;
	if RIGHT
		PLAYER.move.right = 1;
	if BACK
		PLAYER.move.down = 1;
	return (0);
}

int		key_release(int keycode, t_env *env)
{
	if EXIT
	{
		mlx_destroy_window(env->mlx, env->win);
		exit(EXIT_SUCCESS);
	}
	if LEFT
		PLAYER.move.left = 0;
	if FORWARD
		PLAYER.move.up = 0;
	if RIGHT
		PLAYER.move.right = 0;
	if BACK
		PLAYER.move.down = 0;
	return (0);
}

void	turn(t_env *env, char dir)
{
	double	tmpdir;
	double	tmpplain;
	int		coef;

	coef = 1;
	tmpdir = PLAYER.dir.x;
	tmpplain = RAY.plain.x;
	if (dir == '1')
		coef = -1;
	PLAYER.dir.x = PLAYER.dir.x * cos(coef * PLAYER.rspeed)
		- PLAYER.dir.y * sin(coef * PLAYER.rspeed);
	PLAYER.dir.y = tmpdir * sin(coef * PLAYER.rspeed) + PLAYER.dir.y
		* cos(coef * PLAYER.rspeed);
	RAY.plain.x = RAY.plain.x * cos(coef * PLAYER.rspeed)
		- RAY.plain.y * sin(coef * PLAYER.rspeed);
	RAY.plain.y = tmpplain * sin(coef * PLAYER.rspeed)
		+ RAY.plain.y * cos(coef * PLAYER.rspeed);
}

void	move(t_env *env)
{
	if (PLAYER.move.up)
	{
		if (!(MAP.map[(int)(PLAYER.pos.x + PLAYER.dir.x
						* PLAYER.mspeed)][(int)(PLAYER.pos.y)]))
			PLAYER.pos.x += PLAYER.dir.x * PLAYER.mspeed;
		if (!(MAP.map[(int)(PLAYER.pos.x)][(int)(PLAYER.pos.y
						+ PLAYER.dir.y * PLAYER.mspeed)]))
			PLAYER.pos.y += PLAYER.dir.y * PLAYER.mspeed;
	}
	if (PLAYER.move.left)
		turn(env, '0');
	if (PLAYER.move.right)
		turn(env, '1');
	if (PLAYER.move.down)
	{
		if (!(MAP.map[(int)(PLAYER.pos.x - PLAYER.dir.x *
						PLAYER.mspeed)][(int)(PLAYER.pos.y)]))
			PLAYER.pos.x -= PLAYER.dir.x * PLAYER.mspeed;
		if (!(MAP.map[(int)(PLAYER.pos.x)][(int)(PLAYER.pos.y -
						PLAYER.dir.y * PLAYER.mspeed)]))
			PLAYER.pos.y -= PLAYER.dir.y * PLAYER.mspeed;
	}
}
