/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 17:57:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/16 17:00:57 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_barnsley(t_param *param)
{
	param->fr_id = FR_BARNSLEY;
	param->fr_depth = 4200000;
	param->actial_zoom = 50;
	param->display_zoom = 0;
	param->col_step = 0xFFFFFFFF / (double)param->fr_depth;
	param->spec_step = 0.01;
	param->offset_step = 10;
	param->fr_depth_step = 1000;
	param->spec1 = 0.04;
	param->spec2 = 0.85;
	param->offset_x = -0.5;
	param->left_trim = -2.0f;
	param->up_trim = -0.8f;
	param->right_trim = 0.5;
	param->down_trim = 0.8;
}

void	init_mandelbrot(t_param *param)
{
	param->fr_id = FR_MANDELBROT;
	param->fr_depth = 127;
	param->actial_zoom = 150;
	param->display_zoom = 0;
	param->col_step = 0xFFFFFFFF / (double)param->fr_depth;
	param->spec_step = 0.1;
	param->offset_step = 0.04;
	param->fr_depth_step = 1;
	param->spec1 = 4;
	param->spec2 = 1;
	param->offset_x = 0;
	param->offset_y = 0;
	param->i_mouse_move_seed = 0;
	param->r_mouse_move_seed = 0;
	param->left_trim = -1.4f;
	param->up_trim = -0.9f;
	param->right_trim = 0.7;
	param->down_trim = 0.9;
}

void	init_batman(t_param *param)
{
	param->fr_id = FR_BATMAN;
	param->fr_depth = 10;
	param->actial_zoom = 50;
	param->col_step = 0xFFFFFFFF / (double)param->fr_depth;
	param->spec_step = 1;
	param->offset_step = 0.04;
	param->fr_depth_step = 10;
	param->spec1 = 4;
	param->spec2 = 1;
	param->offset_x = 0;
	param->offset_y = 0;
	param->i_mouse_move_seed = 0;
	param->r_mouse_move_seed = 0;
	param->left_trim = -1.5f;
	param->up_trim = -0.8f;
	param->right_trim = 0.5;
	param->down_trim = 0.8;
}

void	init_mandelbrot_cuboid(t_param *param)
{
	param->fr_id = FR_MANDELBROT_CUBOID;
	param->fr_depth = 127;
	param->actial_zoom = 100;
	param->display_zoom = 0;
	param->col_step = 0xFFFFFFFF / (double)param->fr_depth;
	param->spec_step = 0.1;
	param->offset_step = 0.04;
	param->fr_depth_step = 1;
	param->spec1 = 4;
	param->spec2 = 1;
	param->offset_x = 0;
	param->offset_y = 0;
	param->i_mouse_move_seed = 0;
	param->r_mouse_move_seed = 0;
	param->left_trim = -0.8f;
	param->up_trim = -1.2f;
	param->right_trim = 0.8;
	param->down_trim = 1.2;
}

void	init_julia(t_param *param)
{
	param->fr_id = FR_JULIA;
	param->fr_depth = 127;
	param->actial_zoom = 100;
	param->display_zoom = 0;
	param->col_step = 0xFFFFFFFF / (double)param->fr_depth;
	param->spec_step = 0.1;
	param->offset_step = 0.04;
	param->fr_depth_step = 1;
	param->spec1 = 4;
	param->spec2 = 1;
	param->offset_x = -0.5;
	param->offset_y = 0;
	param->r_mouse_move_seed = -0.7;
	param->i_mouse_move_seed = 0.27015;
	param->left_trim = -1.6f;
	param->up_trim = -1.4f;
	param->right_trim = 1.6;
	param->down_trim = 1.4;
}
