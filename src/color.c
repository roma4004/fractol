/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/17 22:16:22 by dromanic         ###   ########.fr       */
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

int inc_color(int color, int offset)
{
	int mask = 0x000000FF << offset;
	int increment = mask & 0x01010101;

	if (color + increment > color | mask)
		color = color + increment;

	return (color);
}

int		get_color(t_col *col)
{
	return ((col->a << 24) | ((col->r) << 16) | ((col->g) << 8) | (col->b));
}

t_col	*gen_color(t_win *win, int i)
{
//	win->param->color = win->param->color_step * i;
	win->img->col.a = (                         0 + win->img->col.a_offset);
	win->img->col.r = (win->param->color_step * i + win->img->col.r_offset);
	win->img->col.g = (win->param->color_step * i + win->img->col.g_offset);
	win->img->col.b = (win->param->color_step * i + win->img->col.b_offset);
	return (&win->img->col);
}
//double z = sqrt(c.real * c.real + c.imag * c.imag);
//int brightness = 256 * log2(1.75 + n - log2(log2(z))) / log2(double)(maxIterations));
///color(brightness, brightness, 255)
//win->param->fr_spec_color = brightness * brightness * 255;