/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 17:57:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/12/29 18:18:24 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_barnsley(t_param *restrict param)
{
	param->fr_id = FR_FERN;
	param->depth = 4200000;
	param->actial_zoom = 50;
	param->display_zoom = 0;
	param->color_step = 0xFFFFFFFF / (double)param->depth;
	param->spec_step = 0.01;
	param->offset_step = 10;
	param->depth_step = 1000;
	param->hor = 0.04;
	param->ver = 0.85;
	param->offset.x = -param->center.x;
	param->trim.left = -2.0f;
	param->trim.up = -0.8f;
	param->trim.right = 0.5;
	param->trim.down = 0.8;
}

void	init_mandelbrot(t_param *restrict param)
{
	param->fr_id = FR_MANDELBROT;
	param->depth = 127;
	param->actial_zoom = 150;
	param->display_zoom = 0;
	param->color_step = 0xFFFFFFFF / (double)param->depth;
	param->spec_step = 0.1;
	param->offset_step = 0.04;
	param->depth_step = 1;
	param->hor = 4;
	param->ver = 1;
	param->offset.x = 0;
	param->offset.y = 0;
	param->i_move_seed = 0;
	param->r_move_seed = 0;
	param->trim.left = -1.4f;
	param->trim.up = -0.9f;
	param->trim.right = 0.7;
	param->trim.down = 0.9;
}

void	init_batman(t_param *restrict param)
{
	param->fr_id = FR_BATMAN;
	param->depth = 10;
	param->actial_zoom = 50;
	param->color_step = 0xFFFFFFFF / (double)param->depth;
	param->spec_step = 1;
	param->offset_step = 0.04;
	param->depth_step = 10;
	param->hor = 4;
	param->ver = 1;
	param->offset.x = 0;
	param->offset.y = 0;
	param->i_move_seed = 0;
	param->r_move_seed = 0;
	param->trim.left = -1.5f;
	param->trim.up = -0.8f;
	param->trim.right = 0.5;
	param->trim.down = 0.8;
}

void	init_mandelbrot_cuboid(t_param *restrict param)
{
	param->fr_id = FR_CUBOID;
	param->depth = 127;
	param->actial_zoom = 100;
	param->display_zoom = 0;
	param->color_step = 0xFFFFFFFF / (double)param->depth;
	param->spec_step = 0.1;
	param->offset_step = 0.04;
	param->depth_step = 1;
	param->hor = 4;
	param->ver = 1;
	param->offset.x = 0;
	param->offset.y = 0;
	param->i_move_seed = 0;
	param->r_move_seed = 0;
	param->trim.left = -0.8f;
	param->trim.up = -1.2f;
	param->trim.right = 0.8;
	param->trim.down = 1.2;
}

void	init_julia(t_param *restrict param)
{
	param->fr_id = FR_JULIA;
	param->depth = 127;
	param->actial_zoom = 100;
	param->display_zoom = 0;
	param->color_step = 0xFFFFFFFF / (double)param->depth;
	param->spec_step = 0.1;
	param->offset_step = 0.04;
	param->depth_step = 1;
	param->hor = 4;
	param->ver = 1;
	param->offset.x = -0.5;
	param->offset.y = 0;
	param->r_move_seed = -0.7;
	param->i_move_seed = 0.27015;
	param->trim.left = -1.6f;
	param->trim.up = -1.4f;
	param->trim.right = 1.6;
	param->trim.down = 1.4;
}
