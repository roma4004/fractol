/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/08 20:46:33 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "main.h"

static int		change_hue(int color, int offset, int mask_offset)
{
	int mask;
	int increment;

	mask = 0x000000FF << mask_offset;
	increment = mask & 0x01010101;
	if (offset == 1)
		color += increment;
	else
		color -= increment;
	return (color);
}

int				change_color(t_env *win, int key)
{
	int		y;
	int		x;
	int		offset;
	int		chanel;

	if (!(offset = 0) && !win)
		return (0);
	if ((key == A || (key == Z)) && (chanel = ALPHA))
		offset = (key == A) ? 1 : -1;
	else if ((key == S || (key == X)) && (chanel = RED))
		offset = (key == S) ? 1 : -1;
	else if ((key == D || (key == C)) && (chanel = GREEN))
		offset = (key == D) ? 1 : -1;
	else if ((key == F || (key == V)) && !(chanel = BLUE))
		offset = (key == F) ? 1 : -1;
	if (offset && (y = -1))
	{
		while (++y < WIN_HEIGHT && (x = -1))
			while (++x < WIN_WIDTH)
				px_to_img(win->img, x, y,
				change_hue(win->img->data[y * WIN_WIDTH + x], offset, chanel));
		redraw_img(win);
		return (1);
	}
	return (0);
}

static t_col	*gen_color(t_env *win, int i)
{
	double	step;
	t_img	*img;

	img = win->img;
	step = (double)i / (double)win->param->iter;
	img->col.a = 0;
	img->col.r = (int)(9 * (1 - step) * step * step * 255);
	img->col.g = (int)(15 * (1 - step) * (1 - step) * step * 255);
	img->col.b = (int)(8.5 * (1 - step) * (1 - step) * (1 - step) * 255);
	return (&win->img->col);
}

int				get_color(t_env *win, int i)
{
	int		color;
	t_col	*col;

	if (!win->flags->G)
	{
		color = (int)(win->param->color_step * i);
		return (color);
	}
	col = gen_color(win, i);
	return ((col->a << 24) | ((col->r) << 16) | ((col->g) << 8) | (col->b));
}