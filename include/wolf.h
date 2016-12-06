/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 08:22:06 by sallen            #+#    #+#             */
/*   Updated: 2016/12/06 08:22:08 by sallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H

# define WOLF_H
# define WIN_WIDTH	1280
# define WIN_HEIGHT	720

# define K_UP 126
# define K_DOWN 125
# define K_LEFT 123
# define K_RIGHT 124
# define K_NUP 91
# define K_NDOWN 84
# define K_NLEFT 86
# define K_NRIGHT 88
# define K_ESC 53
# define PLAYER env->player
# define MAP env->map
# define RAY env->ray
# define WIN env->win
# define IMG env->img
# define FORWARD (keycode == K_UP || keycode == K_NUP)
# define BACK (keycode == K_DOWN || keycode == K_NDOWN)
# define LEFT (keycode == K_LEFT || keycode == K_NLEFT)
# define RIGHT (keycode == K_RIGHT || keycode == K_NRIGHT)
# define EXIT (keycode == K_ESC)

# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <fcntl.h>
# include "libft.h"

typedef struct	s_coord {
	double		x;
	double		y;
}				t_coord;

typedef struct	s_colors {
	int			red;
	int			green;
	int			blue;
}				t_colors;

typedef struct	s_coordint {
	int			x;
	int			y;
}				t_coordint;

typedef struct	s_move {
	int			up;
	int			left;
	int			right;
	int			down;
}				t_move;

typedef struct	s_ray {
	t_coord		pos;
	t_coord		dir;
	t_coord		plain;
	t_coord		sidedist;
	t_coord		disd;
	t_coord		posmap;
	int			lheight;
	int			ystart;
	int			yend;
}				t_ray;

typedef struct	s_player {
	t_coord		pos;
	t_coord		dir;
	t_coordint	step;
	t_move		move;
	double		rspeed;
	double		mspeed;
	double		hcamerad;
	int			hit;
	int			wallside;
	int			sprint;
}				t_player;

typedef struct	s_map {
	int			**map;
	int			display;
	int			sizex;
	int			sizey;
}				t_map;

typedef struct	s_img {
	void		*img;
	char		*d;
	int			bp;
	int			s;
	int			e;
}				t_img;

typedef struct	s_env {
	void		*win;
	void		*mlx;
	t_img		img;
	t_player	player;
	t_map		map;
	t_ray		ray;
	double		time;
	double		oldtime;
	long int	frametime;
}				t_env;

void			get_timeframe(t_env *e);
int				expose_hook(t_env *t);
int				loop_hook(t_env *e);
int				key_release(int keycode, t_env *e);
int				key_press(int keycode, t_env *e);
int				ft_esc(t_env *env);
int				*utils(char const *s, char c);
void			move(t_env *e);
void			colors(t_env *e, t_colors *c);
void			drawline(int x, t_env *e, t_colors *c);
void			init(t_env *env, char *filename);
void			readfile(t_env *e, char *input);
int				*ft_strsplittoint(char const *s, char c);

#endif
