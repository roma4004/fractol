/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/08 20:56:59 by dromanic         ###   ########.fr       */
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
	t_param	*par;
	t_flags	*fl;

	par = win->param;
	fl = win->flags;
	iter_offset = 0;
	if (((key == NUM_MINUS || key == NINE) && (iter_offset = -par->iter_step))
    || ((key == NUM_PLUS || key == ZERO) && (iter_offset = par->iter_step)))
		if (iter_offset && (par->iter + iter_offset > 0))
		{
			par->iter += iter_offset;
			par->color_step = ((fl->T) ? 0xFFFFFFFF : 0xFFFFFF) / par->iter;
			redraw_fract(win);
			printf("iter ch %d\n", par->iter);
			return (1);
		}
	return (0);
	//
	//	int		sign;
	//	t_param	*par;
	//
	//	par = win->par; printf("iter ch %d\n", par->iter);
	//	sign = 0;
	//	if (((key == NUM_MINUS || key == NINE) && (sign = -1))
	//		|| ((key == NUM_PLUS || key == ZERO) && (sign = 1)))
	//	{
	//		if (par->iter + par->iter_step > 11)
	//		{
	//			par->iter += par->iter_step * sign;
	//			par->color_step = 0xFFFFFFFF / par->iter;
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
	if ((key == PLUS && (par->zoom *= 1.5) && (par->offset_step /= 1.5)  )
	|| (key == MINUS && (par->zoom /= 1.5) && (par->offset_step *= 1.5) ))
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
	t_flags	*fl;
	t_param	*par;
	int		*flag;

	fl = win->flags;
	par = win->param;
	flag = 0;
	if (((key == NUM_1 || key == ONE) && (flag = &fl->n1))
		|| ((key == NUM_2 || key == TWO) && (flag = &fl->n2))
		|| ((key == NUM_3 || key == THREE) && (flag = &fl->n3))
		|| ((key == NUM_4 || key == FOUR) && (flag = &fl->n4))
		|| ((key == NUM_5 || key == FIVE) && (flag = &fl->n5))
		|| ((key == NUM_6 || key == SIX) && (flag = &fl->n6))
		|| ((key == NUM_7 || key == SEVEN) && (flag = &fl->n7))
		|| ((key == NUM_8 || key == EIGHT) && (flag = &fl->n8))
		|| (key == Q && (flag = &fl->Q)) || (key == W && (flag = &fl->W))
		|| (key == E && (flag = &fl->E)) || ((key == T && (flag = &fl->T))
			&& (par->color_step = ((fl->T) ? 0xFFFFFFFF : 0xFFFFFF) / par->iter))
		|| (key == Y && (flag = &fl->Y)) || (key == G && (flag = &fl->G))
	)
	{
		*flag = (*flag == 0) ? 1 : 0;
		redraw_fract(win);
		return (1);
	}
	return (0);
}
