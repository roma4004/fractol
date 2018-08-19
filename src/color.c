/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/19 17:33:31 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		change_hue(int color, int offset, int mask_offset)
{
	int mask;
	int increment;

	mask = 0x000000FF << mask_offset;
	increment = mask & 0x01010101;
	if (offset == 1)
	{
		//if ((color + increment) < (color | mask))
			color += increment;
	}
	else
	{
		//if ((color - increment) > (color & ~mask));
			color -= increment;
	}
	//printf("change_color, pre color %d, new color %d\n", prev_col, color);
	return (color);
}

int		get_color(t_col *col)
{
	return ((col->a << 24) | ((col->r) << 16) | ((col->g) << 8) | (col->b));
}

t_col	*gen_color(t_win *win, int i)
{
	double step;
	t_img *img;

	img = win->img;
	step = (double)i / (double)win->param->iter;
	img->col.a = 0;
	img->col.r = (int)(9 * (1 - step) * step * step * 255);
	img->col.g = (int)(15 * (1 - step) * (1 - step) * step * 255);
	img->col.b = (int)(8.5 * (1 - step) * (1 - step) * (1 - step) * 255);
	return (&win->img->col);
}
