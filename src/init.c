/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2018/12/17 13:41:01 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_param	*init_param(void)
{
	t_param *new_param;

	if ((new_param = (t_param *)malloc(sizeof(t_param))))
	{
		new_param->ratio = (int)(WIN_WIDTH / WIN_HEIGHT);
		new_param->center.x = (int)(WIN_WIDTH / 2);
		new_param->center.y = (int)(WIN_HEIGHT / 2);
		new_param->cores = ft_get_processors_num();
		new_param->threads = new_param->cores;
		new_param->spec_step = 1;
		new_param->offset_step = 0.5;
		new_param->depth_step = 1;
		new_param->actial_zoom = 50;
		new_param->offset.x = 0;
		new_param->offset.y = 0;
		new_param->i_mouse_move_seed = 0;
		new_param->r_mouse_move_seed = 0;
		new_param->col_shift.alpha = 0;
		new_param->col_shift.red = 0;
		new_param->col_shift.green = 0;
		new_param->col_shift.blue = 0;
	}
	return (new_param);
}

static t_flags	*init_flags(void)
{
	t_flags	*new_flags;

	if ((new_flags = (t_flags *)malloc(sizeof(t_flags))))
		ft_bzero(new_flags, sizeof(t_flags));
	return (new_flags);
}

t_img			*init_img(void *mlx_ptr, float width, float height)
{
	t_img	*new_img;

	if (!mlx_ptr)
		return (NULL);
	if ((new_img = (t_img *)malloc(sizeof(t_img))))
	{
		new_img->bits_per_pixel = 0;
		new_img->size_line = 0;
		new_img->endian = 0;
		new_img->ptr = mlx_new_image(mlx_ptr, (int)width, (int)height);
		new_img->data = (int *)mlx_get_data_addr(new_img->ptr,
												&new_img->bits_per_pixel,
												&new_img->size_line,
												&new_img->endian);
	}
	return (new_img);
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
	t_env	*new_env;

	if (!(new_env = (t_env *)malloc(sizeof(t_env)))
	|| !(new_env->param = init_param())
	|| !(new_env->flags = init_flags())
	|| !(new_env->mlx_ptr = mlx_init())
	|| !(new_env->win_ptr =
			mlx_new_window(new_env->mlx_ptr,
					(int)WIN_WIDTH, (int)WIN_HEIGHT, WIN_NAME))
	|| !(new_env->img = init_img(new_env->mlx_ptr, WIN_WIDTH, WIN_HEIGHT))
	|| (init_fractal_arr(new_env)))
		free_win(new_env);
	return (new_env);
}
