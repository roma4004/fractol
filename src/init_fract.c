/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 17:57:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/11 21:06:14 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_barnsley(t_param *param)
{
	param->fr_id = FR_BARNSLEY;
	param->i_max = 42000;
	param->zoom = 50;
	param->col_step = 0xFFFFFFFF / param->i_max;
	param->spec_step = 0.01;
	param->offset_step = 10;
	param->iter_step = 1000;
	param->spec1 = 0.04;
	param->spec2 = 0.85;
	param->offset_x = -0.5;
}

void	init_mandelbrot(t_param *param)
{
	param->fr_id = FR_MANDELBROT;
	param->i_max = 127;
	param->zoom = 150;
	param->col_step = 0xFFFFFFFF / param->i_max;
	param->spec_step = 0.1;
	param->offset_step = 0.04;
	param->iter_step = 1;
	param->spec1 = 4;
	param->spec2 = 1;
	param->offset_x = 0;
	param->offset_y = 0;
	param->ij_seed = 0;
	param->rj_seed = 0;
}

void	init_batman(t_param *param)
{
	param->fr_id = FR_BATMAN;
	param->i_max = 10;
	param->zoom = 50;
	param->col_step = 0xFFFFFFFF / param->i_max;
	param->spec_step = 1;
	param->offset_step = 0.04;
	param->iter_step = 10;
	param->spec1 = 4;
	param->spec2 = 1;
	param->offset_x = 0;
	param->offset_y = 0;
	param->ij_seed = 0;
	param->rj_seed = 0;
}

void	init_mandelbrot_cuboid(t_param *param)
{
	param->fr_id = FR_MANDELBROT_CUBOID;
	param->i_max = 127;
	param->zoom = 100;
	param->col_step = 0xFFFFFFFF / param->i_max;
	param->spec_step = 0.1;
	param->offset_step = 0.04;
	param->iter_step = 1;
	param->spec1 = 4;
	param->spec2 = 1;
	param->offset_x = 0;
	param->offset_y = 0;
	param->ij_seed = 0;
	param->rj_seed = 0;
}

void	init_julia(t_param *param)
{
	param->fr_id = FR_JULIA;
	param->i_max = 127;
	param->zoom = 100;
	param->col_step = 0xFFFFFFFF / param->i_max;
	param->spec_step = 0.1;
	param->offset_step = 0.04;
	param->iter_step = 1;
	param->spec1 = 4;
	param->spec2 = 1;
	param->offset_x = -0.5;
	param->offset_y = 0;
	param->rj_seed = -0.7;
	param->ij_seed = 0.27015;
}
