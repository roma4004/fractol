/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 17:57:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/05 21:08:23 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_barnsley(t_param *param)
{
	param->fr_id = FR_BARNSLEY;
	param->iter = 42000;
	param->zoom = 50;
	param->color_step = 0xFFFFFFFF / param->iter;
	param->zoom_x = param->zoom * param->center_x;
	param->zoom_y = param->zoom * param->center_y;
	//param->color_step = 0xffffff / param->iter * PI; // / 1114112;
	param->spec_step = 1;
	param->offset_step = 10;
	param->iter_step = 1000;
	param->spec1 = 0.04;
	param->spec2 = 0.85;
	param->offset_x = -0.5;
}

void	init_mandelbrot(t_param *param)
{
	param->fr_id = FR_MANDELBROT;
	param->iter = 50;
	param->zoom = 150;
	//param->color = DEF_COLOR;
	param->color_step = 0xFFFFFFFF / param->iter;
	param->zoom_x = param->zoom * param->center_x;
	param->zoom_y = param->zoom * param->center_y;
	//param->color_step = 0xffffff / param->iter * PI; // / 1114112;
	param->spec_step = 0.1;
	param->offset_step = 0.04;
	param->iter_step = 1;
	param->spec1 = 4;
	param->spec2 = 2;
	//param->color = DEF_COLOR;
	//	param->zoom = ZOOM_DEFAULT;
	param->offset_x = 0;
	param->offset_y = 0;
}

void	init_batman(t_param *param)
{
	param->fr_id = FR_BATMAN;
	param->iter = 10;
	param->zoom = 50;
	//	param->zoom = ZOOM_DEFAULT;
	//param->color = DEF_COLOR;
	param->color_step = 0xFFFFFFFF / param->iter;
	param->zoom_x = param->zoom * param->center_x;
	param->zoom_y = param->zoom * param->center_y;
	//param->color_step = 0xffffff / param->iter * PI; // / 1114112;
	param->spec_step = 1;
	param->offset_step = 0.04;
	param->iter_step = 10;
	param->spec1 = 4;
	param->spec2 = 2;
	//param->color = DEF_COLOR;
	param->offset_x = 0;
	param->offset_y = 0;
}

void	init_mandelbrot_cuboid(t_param *param)
{
	param->fr_id = FR_MANDELBROT_CUBOID;
	param->iter = 50;
	param->zoom = 0.5;
	//param->color = DEF_COLOR;
	param->color_step = 0xFFFFFFFF / param->iter;
	param->zoom_x = param->zoom * param->center_x;
	param->zoom_y = param->zoom * param->center_y;
	//param->color_step = 0xffffff / param->iter * PI; // / 1114112;
	param->spec_step = 0.1;
	param->offset_step = 0.04;
	param->iter_step = 1;
	param->spec1 = 4;
	param->spec2 = 2;
	//param->color = DEF_COLOR;
	//	param->zoom = ZOOM_DEFAULT;
	param->offset_x = 0;
	param->offset_y = 0;
}