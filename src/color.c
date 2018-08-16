/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/16 19:53:59 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		gen_color(t_win *win, int i)
{
	win->param->color = win->param->color_step * i;
	return (win->param->color);
}
//double z = sqrt(c.real * c.real + c.imag * c.imag);
//int brightness = 256 * log2(1.75 + n - log2(log2(z))) / log2(double)(maxIterations));
///color(brightness, brightness, 255)
//win->param->fr_spec_color = brightness * brightness * 255;