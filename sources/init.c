/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2018/12/29 18:07:03 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_param	*init_param(void)
{
	t_param *param;

	if ((param = (t_param *)malloc(sizeof(t_param))))
	{
		ft_bzero(param, sizeof(t_param));
		param->center.x = W_WIDTH / 2.0f;
		param->center.y = W_HEIGHT / 2.0f;
		param->cores = ft_get_processors_num();
		param->threads = param->cores;
		param->spec_step = 1;
		param->offset_step = 0.5;
		param->depth_step = 1;
		param->actial_zoom = 50;
	}
	return (param);
}

static t_flags	*init_flags(void)
{
	t_flags	*new_flags;

	if ((new_flags = (t_flags *)malloc(sizeof(t_flags))))
		ft_bzero(new_flags, sizeof(t_flags));
	return (new_flags);
}

int				init_fractal_arr(t_env *env)
{
	env->names[0] = "Mandelbrot";
	env->get_px[0] = get_mandelbrot;
	env->init_func[0] = init_mandelbrot;
	env->names[1] = "Julia";
	env->get_px[1] = get_julia;
	env->init_func[1] = init_julia;
	env->names[2] = "Fern";
	env->get_px[2] = draw_barnsley;
	env->init_func[2] = init_barnsley;
	env->names[3] = "Cuboid";
	env->get_px[3] = get_mandelbrot_cuboid;
	env->init_func[3] = init_mandelbrot_cuboid;
	env->names[4] = "Batman";
	env->get_px[4] = get_batman;
	env->init_func[4] = init_batman;
	return (0);
}

t_env			*init_env(void)
{
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env)))
	|| !(env->param = init_param())
	|| !(env->flags = init_flags())
	|| !(env->mlx_ptr = mlx_init())
	|| !(env->win_ptr = mlx_new_window(env->mlx_ptr, W_WIDTH, W_HEIGHT, W_NAME))
	|| !(env->img_ptr = mlx_new_image(env->mlx_ptr, W_WIDTH, W_HEIGHT))
	|| !(env->img_data = (int *)mlx_get_data_addr(env->img_ptr,
												&env->param->bits_per_pixel,
												&env->param->size_line,
												&env->param->endian))
	|| (init_fractal_arr(env)))
		free_win(env);
	return (env);
}

int				free_win(t_env *env)
{
	if (env)
	{
		if (env->param)
			ft_memdel((void *)&env->param);
		if (env->flags)
			ft_memdel((void *)&env->flags);
		if (env->mlx_ptr && env->img_ptr)
			mlx_destroy_image(env->mlx_ptr, env->img_ptr);
		ft_memdel((void *)&env);
		return (1);
	}
	return (0);
}
