/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:21:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/07 21:56:19 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		input_fract(t_env *win, char *name)
{
	win->param->fr_id = -1;
	if (((ft_strcmp(name, "Barnsley")) == 0)
		|| (ft_strcmp(name, "B")) == 0)
	win->param->fr_id = FR_BARNSLEY;
	else if (((ft_strcmp(name, "Mandelbrot")) == 0)
		 || (ft_strcmp(name, "M")) == 0)
			win->param->fr_id = FR_MANDELBROT;
	else if (((ft_strcmp(name, "Batman")) == 0)
		 || (ft_strcmp(name, "BM")) == 0)
			win->param->fr_id = FR_BATMAN;
	else if (((ft_strcmp(name, "Mandelbrot_cuboid")) == 0)
		 || (ft_strcmp(name, "MC")) == 0)
			win->param->fr_id = FR_MANDELBROT_CUBOID;
	else if (((ft_strcmp(name, "Julia")) == 0)
		 || (ft_strcmp(name, "J")) == 0)
			win->param->fr_id = FR_JULIA;
	return (-1);
}