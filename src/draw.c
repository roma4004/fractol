/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/02 20:43:56 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	change_fract(t_env *win, int fr_new_type)
{
	win->param->fr_id = fr_new_type;
	init_mandelbrot(win->param);
	redraw_fract(win);
}

void	redraw_img(t_env *win)
{
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr,
							win->img->ptr, 0, 0);
}

void		redraw_fract(t_env *win)
{
	if (win->param->fr_id == FR_BARNSLEY)
		draw_barnsley(clear_img(win));
	else
		parallel_draw_fractal(win);
	if (win->flags->interface_on)
		show_interface(win);
}

static void	barnsley_part(t_env *win, char part, t_cnb *c)
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

void	draw_barnsley(t_env *win)
{
	float		rng;
	long		n;
	t_coords	i;
	t_cnb		c;
	t_param		*par;

	c = (t_cnb){.newR = 0, .newI = 0};
	par = win->param;
	n = par->iter;
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
		i.x = (int)((c.newR + 4) * par->zoom - par->offset_x) ;
		i.y = (int)(WIN_HEIGHT - c.newI * par->zoom - par->offset_y);
		px_to_img(win->img->ptr, i.x, i.y, DEF_COLOR);
	}
	redraw_img(win);
}
