/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/19 18:49:25 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


void	redraw_fract(t_win *win)
{
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	if (win->param->fr_id == FR_BARNSLEY)
		draw_barnsley(clear_img(win));
	else
		draw_fractal(win);
	if (win->flags->interface_on)
		show_interface(win);
}
static void	barnsley_part(t_win *win, char part, t_cnb *c)
{
	if (part == BARNSLEY_PART_BODY)
	{
		c->newR = 0;
		c->newI = 0.16f * c->newI;
	}
	else if (part == BARNSLEY_PART_RIGHT)
	{
		c->newR = -0.15f * c->newR + 0.28f * c->newI;
		c->newI = 0.26f * c->newR + 0.24f * c->newI + 0.44f;
	}
	else if (part == BARNSLEY_PART_LEFT)
	{
		c->newR = 0.2f * c->newR + -0.26f * c->newI;
		c->newI = 0.23f * c->newR + 0.22f * c->newI + 1.6f;
	}
	else
	{
		c->newR =  0.85 * c->newR + win->param->spec1 * c->newI;
		c->newI = -0.04 * c->newR + win->param->spec2 * c->newI + 1.6;
	}

}

void	draw_barnsley(t_win *win)
{
	float		rng;
	long		n;
	t_coords	i;
	t_cnb		c;

	c = (t_cnb){.newR = 0, .newI = 0};
	n = win->param->iter;
	while (n--)
	{
		rng = ((float)rand()) / RAND_MAX;
		if (rng <= 0.01f)
			barnsley_part(win, BARNSLEY_PART_BODY, &c);
		else if (rng <= 0.06f)
			barnsley_part(win, BARNSLEY_PART_RIGHT, &c);
		else if (rng <= 0.14f)
			barnsley_part(win, BARNSLEY_PART_LEFT, &c);
		else
			barnsley_part(win, BARNSLEY_PART_CURVE, &c);
		i.x = (c.newR + 4) * win->param->zoom - win->param->offset_x ;
		i.y = WIN_HEIGHT - c.newI * win->param->zoom - win->param->offset_y;
		if (i.x < 0 || i.y < 0 || i.x > WIN_WIDTH || i.y > WIN_HEIGHT)
			continue ;
		px_to_img(win->img->img_ptr, i.x, i.y, DEF_COLOR);
	}
	redraw_img(win);
}
