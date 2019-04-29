/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/20 21:12:51 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_param	init_param(void)
{
	t_param		param;

	ft_bzero(&param, sizeof(t_param));
	param.center = (t_db_pt){ W_WIDTH / 2.0, W_HEIGHT / 2.0 };
	param.cores = ft_get_processors_num();
	param.threads = param.cores;
	param.spec_step = 1;
	param.offset_step = 0.5;
	param.depth_step = 1;
	param.actial_zoom = 50;
	return (param);
}

static int		init_fractal_arr(t_env *restrict env)
{
	env->fract_names[0] = MSG_FRACT_MANDEL;
	env->get_px_func[0] = get_mandelbrot;
	env->init_func[0] = init_mandelbrot;
	env->fract_names[1] = MSG_FRACT_JULIA;
	env->get_px_func[1] = get_julia;
	env->init_func[1] = init_julia;
	env->fract_names[2] = MSG_FRACT_BARNSL;
	env->get_px_func[2] = draw_barnsley;
	env->init_func[2] = init_barnsley;
	env->fract_names[3] = MSG_FRACT_CUBOID;
	env->get_px_func[3] = get_mandelbrot_cuboid;
	env->init_func[3] = init_mandelbrot_cuboid;
	env->fract_names[4] = MSG_FRACT_BATMAT;
	env->get_px_func[4] = get_batman;
	env->init_func[4] = init_batman;
	return (0);
}

t_env			*init_env(t_env *restrict env)
{
	env->param = init_param();
	ft_bzero(&env->flags, sizeof(t_flags));
	if (!(env->mlx_ptr = mlx_init())
	|| !(env->win_ptr = mlx_new_window(env->mlx_ptr, W_WIDTH, W_HEIGHT, W_NAME))
	|| !(env->img_ptr = mlx_new_image(env->mlx_ptr, W_WIDTH, W_HEIGHT))
	|| !(env->surf = (t_uint32_unalign *)mlx_get_data_addr(env->img_ptr,
												&env->param.bits_per_pixel,
												&env->param.size_line,
												&env->param.endian))
	|| (init_fractal_arr(env)))
		exit_x(env);
	return (env);
}
