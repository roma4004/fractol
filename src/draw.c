/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/14 20:02:01 by jdoeanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	redraw_fract(t_win *win)
{
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	if (win->param->fr_id == FR_BARNSLEY)
		draw_barnsley(win);
	else
		draw_fractal(win);
	if (win->flags->interface_on)
		show_interface(win);
}

void	draw_barnsley(t_win *win)
{
	win->param->fr_id = FR_BARNSLEY;
	float		rng;
	long		n;
	t_coords	i;
	t_cnb		c;

	c = (t_cnb){.newR = 0, .newI = 0};
	//float prob[4] = {0.01, 0.06, 0.08, 0.85};
	n = win->param->iter;
	while (n--)
	{
		rng = ((float)rand()) / RAND_MAX;
		if (rng <= 0.01f)
		{//body
			c.newR = 0;
			c.newI = 0.16f * c.newI;
		}
		else if (rng <= 0.06f)
		{//right part
			c.newR = -0.15f * c.newR + 0.28f * c.newI;
			c.newI = 0.16f * c.newR + 0.24f * c.newI + 0.44f;
		}
		else if (rng <= 0.24f)
		{//left part
			c.newR = 0.2f * c.newR + -0.26f * c.newI;
			c.newI = 0.23f * c.newR + 0.22f * c.newI + 1.6f;
		}
		else
		{
			c.newR = 0.85 * c.newR + win->param->spec1 * c.newI;
			c.newI = -0.04 * c.newR + win->param->spec2 * c.newI + 1.6;
		}
		i.x = win->param->offset_x +        (c.newR + 4) * win->param->zoom;
		i.y = win->param->offset_y + WIN_HEIGHT - c.newI * win->param->zoom;

		if (i.x < 0 || i.y < 0 || i.x > WIN_WIDTH || i.y > WIN_HEIGHT)
			continue ;
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, (int)i.x, (int)i.y, DEF_COLOR);
	}
}