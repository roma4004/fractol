/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/18 19:37:24 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//a = 0x678FA0FE
//b = 0x00FF0000 = 0x000000FF << 16
//c = b & 0x01010101 = 0x00010000
//if (a + c > a | b)
//a = a + c;
//color +=	0x00000100
//
//if (color = (color & 0x00FF0000) >> 24 + offset < 255);
//color += 0x00010000;
//if (color = (color & 0xFF000000) >> 24 - offset > 0);
//color -= 0x 00010000;

int		change_hue(int color, int offfset, int mask_offset)
{
	int prev_col;
		prev_col = color;

	int mask = 0x000000FF << mask_offset;
	int increment = mask & 0x01010101;

	if (offfset == 1)
	{
		//if ((color + increment) < (color | mask))
			color += increment;
	}
	//if ((color - increment) > (color & ~mask))
		//color += increment;
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

	step = (double)i/(double)win->param->iter;
	//	win->param->color = win->param->color_step * i;
	img->col.a = (0 + img->col.a_offset);
	img->col.r = (int)(9*(1-step)*step*step*255 + img->col.r_offset);
	img->col.g = (int)(15*(1-step)*(1-step)*step*255 + img->col.g_offset);
	img->col.b = (int)(8.5*(1-step)*(1-step)*(1-step)*255 + img->col.b_offset);
	return (&win->img->col);
}
