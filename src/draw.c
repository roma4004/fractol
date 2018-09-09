/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/09 20:09:44 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		redraw_img(t_env *env)
{
	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr,
							env->img->ptr, 0, 0);
}

void		redraw_fract(t_env *env)
{
	if (env->param->fr_id == FR_BARNSLEY)
		draw_barnsley(clear_img(env));
	else
		parallel_draw_fractal(env);
	if (env->flags->Menu_on)
		show_menu(env, 0, 0);
	if (env->flags->Hints_on)
		show_combo(env, 0, 0);
	if (env->flags->Values_on)
		show_value(env, 0, 0);
}

int			get_fractal_col(t_env *env, int x, int y)
{
	if (env->param->fr_id == FR_JULIA)
		return (julia_col(env, x, y));
	if (env->param->fr_id == FR_BATMAN)
		return (batman_col(env, x, y));
	if (env->param->fr_id == FR_MANDELBROT)
		return (mandelbrot_col(env, x, y));
	if (env->param->fr_id == FR_MANDELBROT_CUBOID)
		return (mandelbrot_cuboid(env, x, y));
	return (0);
}

static void	barnsley_part(t_env *env, char part, t_cnb *c)
{
	if (part == BARNSLEY_PART_BODY)
	{
		c->R = 0;
		c->I = 0.16f * c->I;
	}
	else if (part == BARNSLEY_PART_RIGHT)
	{
		c->R = -0.15f * c->R + 0.28f * c->I;
		c->I = 0.26f * c->R + 0.24f * c->I + 0.44f;
	}
	else if (part == BARNSLEY_PART_LEFT)
	{
		c->R = 0.2f * c->R + -0.26f * c->I;
		c->I = 0.23f * c->R + 0.22f * c->I + 1.6f;
	}
	else
	{
		c->R = 0.85 * c->R + env->param->spec1 * c->I;
		c->I = -0.04 * c->R + env->param->spec2 * c->I + 1.6;
	}
}

void		draw_barnsley(t_env *env)
{
	float		rng;
	long		n;
	t_coords	i;
	t_cnb		c;
	t_param		*par;

	c = (t_cnb){.R = 0, .I = 0};
	par = env->param;
	n = par->iter;
	while (n--)
	{
		rng = ((float)rand()) / RAND_MAX;
		if (rng <= 0.01f)
			barnsley_part(env, BARNSLEY_PART_BODY, &c);
		else if (rng <= 0.06f)
			barnsley_part(env, BARNSLEY_PART_RIGHT, &c);
		else if (rng <= 0.14f)
			barnsley_part(env, BARNSLEY_PART_LEFT, &c);
		else
			barnsley_part(env, BARNSLEY_PART_CURVE, &c);
		i.x = (int)((c.R + 4) * par->zoom - par->offset_x);
		i.y = (int)(WIN_HEIGHT - c.I * par->zoom - par->offset_y);
		px_to_img(env->img->ptr, i.x, i.y, DEF_COLOR);
	}
	redraw_img(env);
}
