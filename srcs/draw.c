/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 08:22:42 by sallen            #+#    #+#             */
/*   Updated: 2016/12/06 08:22:43 by sallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

static void		set_colors(t_colors *c, int red, int green, int blue)
{
	c->red = red;
	c->green = green;
	c->blue = blue;
}

static void		mlx_image_put_pixel(void *mlx, t_img *i, t_coordint p,
		t_colors *c)
{
	if (i->e)
	{
		i->d[p.y * i->s + p.x * i->bp / 8] = mlx_get_color_value(mlx, c->red);
		i->d[p.y * i->s + p.x * i->bp / 8 + 1] =
			mlx_get_color_value(mlx, c->green);
		i->d[p.y * i->s + p.x * i->bp / 8 + 2] =
			mlx_get_color_value(mlx, c->blue);
	}
	else
	{
		i->d[p.y * i->s + i->bp / 8 * p.x] = mlx_get_color_value(mlx, c->blue);
		i->d[p.y * i->s + i->bp / 8 * p.x + 1] =
			mlx_get_color_value(mlx, c->green);
		i->d[p.y * i->s + i->bp / 8 * p.x + 2] =
			mlx_get_color_value(mlx, c->red);
	}
}

void			drawline(int x, t_env *e, t_colors *c)
{
	t_coordint	p;
	t_colors	skyfloor;

	p.x = x;
	e->img.d = mlx_get_data_addr(e->img.img, &e->img.bp, &e->img.s, &e->img.e);
	set_colors(&skyfloor, 0, 0, 204);
	p.y = 0;
	while (p.y < e->ray.ystart)
	{
		mlx_image_put_pixel(e, &(e->img), p, &skyfloor);
		p.y++;
	}
	p.y = e->ray.ystart;
	while (p.y < e->ray.yend)
	{
		mlx_image_put_pixel(e, &(e->img), p, c);
		p.y++;
	}
	set_colors(&skyfloor, 224, 224, 224);
	p.y = e->ray.yend;
	while (p.y < WIN_HEIGHT)
	{
		mlx_image_put_pixel(e, &(e->img), p, &skyfloor);
		p.y++;
	}
}

void			colors(t_env *env, t_colors *c)
{
	int		x;

	x = 0;
	if (PLAYER.wallside == 0)
	{
		if (PLAYER.step.x < 0)
			while (x < 256)
			{
				set_colors(c, 204, 0, 204);
				x++;
			}
		else
			set_colors(c, 0, 204, 102);
	}
	else
	{
		if (PLAYER.step.y < 0)
			set_colors(c, 102, 0, 204);
		else
			set_colors(c, 0, 102, 204);
	}
}
