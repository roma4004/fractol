/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/06 18:19:06 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_param		*init_param(void)
{
	t_param *new_param;

	if ((new_param = (t_param *)malloc(sizeof(t_param))))
	{
		new_param->ratio = WIN_WIDTH / WIN_HEIGHT;
		new_param->center_x = WIN_WIDTH / 2;
		new_param->center_y = WIN_HEIGHT / 2;
		new_param->cpu_cores = get_processors_num();
		new_param->spec_step = 1;
		new_param->offset_step = 0.05;
		new_param->iter_step = 1;
		new_param->spec1 = 4;
		new_param->spec2 = 2;
		//param->color = DEF_COLOR;
		new_param->zoom = ZOOM_DEFAULT;
		new_param->offset_x = 0;
		new_param->offset_y = 0;
		//init_mandelbrot(new_param);
	}
	return (new_param);
}

static t_flags		*init_flags(void)
{
	t_flags	*new_flags;

	if ((new_flags = (t_flags *)malloc(sizeof(t_flags))))
	{
		new_flags->n0 = 0;
		new_flags->n1 = 0;
		new_flags->n2 = 0;
		new_flags->n3 = 0;
		new_flags->n4 = 0;
		new_flags->n5 = 0;
		new_flags->n6 = 0;
		new_flags->n7 = 0;
		new_flags->n8 = 0;
		new_flags->n9 = 0;
		new_flags->Q = 0;
		new_flags->W = 0;
		new_flags->E = 0;
		new_flags->T = 1;
		new_flags->Y = 1;
		new_flags->color_type = 0;
		new_flags->interface_on = 0;
		new_flags->error_code = 0;
		new_flags->lock_julia = 0;
	}
	return (new_flags);
}

t_img	*init_img(void *mlx_ptr, int width, int height)
{
	t_img *new_img;

	if (!mlx_ptr)
		return (NULL);
	if ((new_img = (t_img *)malloc(sizeof(t_img))))
	{
		//		new_img->col.a = 0;
		//		new_img->col.R = 0;
		//		new_img->col.g = 0;
		//		new_img->col.b = 0;
		new_img->bits_per_pixel = 0;
		new_img->size_line = 0;
		new_img->endian = 0;
		new_img->ptr = mlx_new_image(mlx_ptr, width, height);
		new_img->data = (int *)mlx_get_data_addr(new_img->ptr,
												 &new_img->size_line,
												 &new_img->bits_per_pixel,
												 &new_img->endian);
	}
	return (new_img);
}

t_env			*init_win(void)
{
	t_env	*new_win;

	if (!(new_win = (t_env *)malloc(sizeof(t_env)))
		|| !(new_win->param = init_param())
		|| !(new_win->flags = init_flags())
		|| !(new_win->mlx_ptr = mlx_init())
		|| !(new_win->win_ptr =
			 mlx_new_window(new_win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, WIN_NAME))
		|| !(new_win->img = init_img(new_win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT))
		|| !(new_win->init_func[0] = init_barnsley)
		|| !(new_win->init_func[1] = init_mandelbrot)
		|| !(new_win->init_func[2] = init_batman)
		|| !(new_win->init_func[3] = init_mandelbrot_cuboid)
		|| !(new_win->init_func[4] = init_julia)
	)
		free_win(new_win);
	return (new_win);
}
