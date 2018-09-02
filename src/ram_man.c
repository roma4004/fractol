/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ram_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:23:50 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/19 18:47:15 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		free_win(t_env *win)
{
	if (win)
	{
		if (win->param)
			ft_memdel((void *)&win->param);
		ft_memdel((void *)&win->flags);
		//ft_memdel((void *)&win->img); need to free img func for inner pointers
		ft_memdel((void *)&win);
		return (1);
	}
	return (0);
}

t_env	*clear_img(t_env *win)
{
	int		y;
	int		x;

	y = -1;
	while (++y < WIN_HEIGHT && (x = -1))
		while (++x < WIN_WIDTH)
			win->img->data[y * (int)WIN_WIDTH + x] = 0;
	return (win);
}

int		exit_x(t_env *win)
{
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	free_win(win);
	exit(0);
}
