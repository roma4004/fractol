/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/03 20:51:31 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			map_offset(t_env *win, int key)
{
	double	offset_x;
	double	offset_y;

	if (!win)
		return (0);
	offset_x = 0;
	offset_y = 0;
	if ((key == ARROW_LEFT && (offset_x = win->param->offset_step))
	|| (key == ARROW_UP && (offset_y = win->param->offset_step))
	|| (key == ARROW_DOWN && (offset_y = -win->param->offset_step))
	|| (key == ARROW_RIGHT && (offset_x = -win->param->offset_step)))
	{
		win->param->offset_x += offset_x;
		win->param->offset_y += offset_y;
		redraw_fract(win);
		return (1);
	}
	return (0);
}

int			specific_param(t_env *win, int key)
{
	int		need_redraw;
	t_param	*param;

	param = win->param;
	need_redraw = 0;
	if ((key == PAGE_UP || key == PAGE_DOWN) && (need_redraw = 1))
		param->spec2 += (key == PAGE_UP) ? param->spec_step : -param->spec_step;
	else if ((key == HOME || key == END) && (need_redraw = 1))
		param->spec1 += (key == HOME) ? -param->spec_step : param->spec_step;
	if (need_redraw)
	{
		redraw_fract(win);
		return (1);
	}
	return (0);
}

int			iterate_change(t_env *win, int key)
{
	int		iter_offset;
	t_param	*param;

	param = win->param;
	printf("iter ch %d\n", param->iter);
	iter_offset = 0;
	if (((key == NUM_MINUS || key == NINE) && (iter_offset = -param->iter_step))
    || ((key == NUM_PLUS || key == ZERO) && (iter_offset = param->iter_step)))
		if (iter_offset && (param->iter + iter_offset > 0))
		{
			param->iter += iter_offset;
			param->color_step = 0xFFFFFFFF / param->iter;
			redraw_fract(win);
			return (1);
		}
	return (0);
	//
	//	int		sign;
	//	t_param	*param;
	//
	//	param = win->param; printf("iter ch %d\n", param->iter);
	//	sign = 0;
	//	if (((key == NUM_MINUS || key == NINE) && (sign = -1))
	//		|| ((key == NUM_PLUS || key == ZERO) && (sign = 1)))
	//	{
	//		if (param->iter + param->iter_step > 11)
	//		{
	//			param->iter += param->iter_step * sign;
	//			param->color_step = 0xFFFFFFFF / param->iter;
	//			redraw_fract(win);
	//		}
	//		return (1);
	//	}
	//	return (0);

}

int			zoom(t_env *win, int key, float x, float y)
{
	t_param	*par;

	par = win->param;
	if ((key == PLUS && (par->zoom *= 1.5) )
	|| (key == MINUS && (par->zoom /= 1.5) ))
	{
		par->offset_x += (x - par->center_x) * par->center_x / (par->zoom * WIN_WIDTH);
		par->offset_y += (y - par->center_y) * par->center_y / (par->zoom * WIN_HEIGHT);
		//par->iter += 10;
		//printf("%f\n", par->zoom);
		redraw_fract(win);
		//or
		// win->param->offset_x += (x - WIN_WIDTH / 2)
		// 							/ ((WIN_WIDTH / 2) * win->param->zoom);
		//win->param->offset_y += (y - WIN_HEIGHT / 2)
		// 							/ ((WIN_HEIGHT / 2) * win->param->zoom);
		return (1);
	}
	return (0);
}

int			toggles(t_env *win, int key)
{
	t_flags	*flags;
	int		*flag;

	flags = win->flags;
	flag = 0;
	if (((key == NUM_1 || key == ONE) && (flag = &flags->man_1))
		|| ((key == NUM_2 || key == TWO) && (flag = &flags->man_2))
		|| ((key == NUM_3 || key == THREE) && (flag = &flags->man_3))
		|| ((key == NUM_4 || key == FOUR) && (flag = &flags->man_4))
		|| ((key == NUM_5 || key == FIVE) && (flag = &flags->man_5))
		|| ((key == NUM_6 || key == SIX) && (flag = &flags->man_6))
		|| ((key == NUM_7 || key == SEVEN) && (flag = &flags->man_7))
		|| ((key == NUM_8 || key == EIGHT) && (flag = &flags->man_8)))
	{
		*flag = (*flag == 0) ? 1 : 0;
		redraw_fract(win);
		return (1);
	}
	return (0);
}
