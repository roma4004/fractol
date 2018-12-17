/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ram_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:23:50 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/16 17:16:55 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_env		*clear_img(t_env *env)
{
	int		y;
	int		x;

	y = -1;
	while (++y < (int)WIN_HEIGHT)
	{
		x = -1;
		while (++x < (int)WIN_WIDTH)
			env->img->data[y * (int)WIN_WIDTH + x] = 0;
	}
	return (env);
}

static int	free_img(t_env *env, t_img *img)
{
	if (env && img)
	{
		if (env->mlx_ptr && img->ptr)
			mlx_destroy_image(env->mlx_ptr, img->ptr);
		ft_memdel((void *)&img);
		return (1);
	}
	return (0);
}

int			free_win(t_env *env)
{
	if (env)
	{
		if (env->param)
			ft_memdel((void *)&env->param);
		if (env->flags)
			ft_memdel((void *)&env->flags);
		free_img(env, env->img);
		ft_memdel((void *)&env);
		return (1);
	}
	return (0);
}

int			exit_x(t_env *env)
{
	mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	free_win(env);
	exit(0);
}
