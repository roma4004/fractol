/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/30 17:02:15 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


static t_param		*init_param(void)
{
	t_param *new_param;

	if ((new_param = (t_param *)malloc(sizeof(t_param))))
	{
		init_fract(new_param, FR_BARNSLEY);
		new_param->cpu_cores = get_processors_num();
	}
	return (new_param);
}

static t_flags		*init_flags(void)
{
	t_flags	*new_flags;

	if ((new_flags = (t_flags *)malloc(sizeof(t_flags))))
	{
		new_flags->man_1 = 0;
		new_flags->man_2 = 0;
		new_flags->man_3 = 0;
		new_flags->man_4 = 0;
		new_flags->man_5 = 0;
		new_flags->man_6 = 0;
		new_flags->man_7 = 0;
		new_flags->color_type = 0;
		new_flags->interface_on = 0;
		new_flags->error_code = 0;
	}
	return (new_flags);
}


t_win			*init_win(void)
{
	t_win	*new_win;

	if (!(new_win = (t_win *)malloc(sizeof(t_win)))
		|| !(new_win->param = init_param())
		|| !(new_win->flags = init_flags())
		|| !(new_win->mlx_ptr = mlx_init())
		|| !(new_win->win_ptr =
			 mlx_new_window(new_win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, WIN_NAME))
		|| !(new_win->img = init_img(new_win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT)))
		free_win(new_win);
	return (new_win);
}
