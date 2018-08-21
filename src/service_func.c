/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 19:23:35 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/20 13:37:38 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

double	pow_of(double num, int exp)
{
	double result;

	result = 1.0;
	while (exp > 0)
	{
		if (exp % 2 == 1)
			result *= num;
		exp >>= 1;
		num *= num;
	}
	return (result);
}

int		toggle_param(int *param)
{//maybe need remove this func to ternary if
	*param = (*param == 0) ? 1 : 0;
	return (1);
}

void	px_to_img(t_img *img, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		img->data[y * WIN_WIDTH + x] = color;
}

void	redraw_img(t_win *win)
{
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr,
							win->img->img_ptr, 0, 0);
}


int		get_processors_num(void)
{
	int		nm[2];
	size_t	count;
	size_t	len;

	len = 4;
	nm[0] = CTL_HW;
	nm[1] = HW_AVAILCPU;
	sysctl(nm, 2, &count, &len, NULL, 0);
	if(count < 1)
	{
		nm[1] = HW_NCPU;
		sysctl(nm, 2, &count, &len, NULL, 0);
		if(count < 1)
			count = 1;
	}
	return (count);
}
