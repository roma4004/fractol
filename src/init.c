/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/12 16:28:12 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_param	*init_param(void)
{
	t_param *new_param;

	if ((new_param = (t_param *)malloc(sizeof(t_param))))
	{
		new_param->ratio = WIN_WIDTH / WIN_HEIGHT;
		new_param->center_x = WIN_WIDTH / 2;
		new_param->center_y = WIN_HEIGHT / 2;
		new_param->cores = ft_get_processors_num();
		new_param->threads = new_param->cores;
		new_param->spec_step = 1;
		new_param->offset_step = 0.5;
		new_param->i_step = 1;
		new_param->zoom = 50;
		new_param->offset_x = 0;
		new_param->offset_y = 0;
		new_param->ij_seed = 0;
		new_param->rj_seed = 0;
		new_param->alpha_shift = 0;
		new_param->red_shift = 0;
		new_param->green_shift = 0;
		new_param->blue_shift = 0;
	}
	return (new_param);
}

int				flag_reset(t_flags *flags)
{
	if (!flags)
		return (0);
	flags->n1 = 0;
	flags->n2 = 0;
	flags->n3 = 0;
	flags->n4 = 0;
	flags->n5 = 0;
	flags->n6 = 0;
	flags->n7 = 0;
	flags->n8 = 0;
	flags->q = 0;
	flags->w = 0;
	flags->e = 0;
	flags->col_range = 0;
	flags->if_carioid = 0;
	flags->alt_color = 0;
	flags->hints_on = 1;
	flags->values_on = 1;
	flags->menu_on = 1;
	flags->lock_julia = 0;
	flags->green_text = 0;
	return (1);
}

static t_flags	*init_flags(void)
{
	t_flags	*new_flags;

	if ((new_flags = (t_flags *)malloc(sizeof(t_flags))))
		flag_reset(new_flags);
	return (new_flags);
}

t_img			*init_img(void *mlx_ptr, int width, int height)
{
	t_img *new_img;

	if (!mlx_ptr)
		return (NULL);
	if ((new_img = (t_img *)malloc(sizeof(t_img))))
	{
		new_img->col.a = 0;
		new_img->col.r = 0;
		new_img->col.g = 0;
		new_img->col.b = 0;
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
		|| !(new_win->init_func[4] = init_julia))
		free_win(new_win);
	return (new_win);
}
