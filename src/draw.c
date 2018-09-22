/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/22 18:35:32 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		redraw_fract_or_img(t_env *env, int img_only)
{
	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr,
							env->img->ptr, 0, 0);
	if (!env->flags->menu_off)
		show_menu(env, 20, 10, env->flags);
	if (!env->flags->hints_off)
		show_combo(env, 20, 10);
	if (!env->flags->values_off)
		show_values(env, 20, 10);
	if (img_only)
		return ;
	if (env->param->fr_id == FR_BARNSLEY)
	{
		clear_img(env);
		draw_barnsley(env, env->param);
	}
	else
		parallel_draw(env, env->param->threads);
}

int			get_fractal_color(t_param *param, t_flags *flags, int x, int y)
{
	if (param->fr_id == FR_JULIA)
		return (get_julia(param, flags, x, y));
	if (param->fr_id == FR_BATMAN)
		return (get_batman(param, flags, x, y));
	if (param->fr_id == FR_MANDELBROT)
		return (get_mandelbrot(param, flags, x, y));
	if (param->fr_id == FR_MANDELBROT_CUBOID)
		return (get_mandelbrot_cuboid(param, flags, x, y));
	return (0);
}

static void	barnsley_part(t_env *env, char part, t_cnb *c)
{
	double r_new;
	double i_new;

	r_new = c->r;
	i_new = c->i;
	if (part == BARNSLEY_PART_BODY)
	{
		c->r = 0;
		c->i = 0.16f * i_new;
	}
	else if (part == BARNSLEY_PART_RIGHT)
	{
		c->r = -0.15f * r_new + 0.28f * i_new;
		c->i = 0.26f * r_new + 0.24f * i_new + 0.44f;
	}
	else if (part == BARNSLEY_PART_LEFT)
	{
		c->r = 0.2f * r_new + -0.26f * i_new;
		c->i = 0.23f * r_new + 0.22f * i_new + 1.6f;
	}
	else
	{
		c->r = 0.85 * r_new + env->param->spec1 * i_new;
		c->i = -0.04 * r_new + env->param->spec2 * i_new + 1.6;
	}
}

void		draw_barnsley(t_env *env, t_param *par)
{
	int			x;
	int			y;
	float		rng;
	long long	n;
	t_cnb		c;

	c = (t_cnb){.r = 0, .i = 0};
	n = par->fr_depth;
	while (n--)
	{
		rng = (float)rand() / (float)RAND_MAX;
		if (rng <= 0.01f)
			barnsley_part(env, BARNSLEY_PART_BODY, &c);
		else if (rng <= 0.06f)
			barnsley_part(env, BARNSLEY_PART_RIGHT, &c);
		else if (rng <= 0.14f)
			barnsley_part(env, BARNSLEY_PART_LEFT, &c);
		else
			barnsley_part(env, BARNSLEY_PART_CURVE, &c);
		x = (int)((c.r + 4) * par->actial_zoom - par->offset_x);
		y = (int)(WIN_HEIGHT - c.i * par->actial_zoom - par->offset_y);
		px_to_img(env->img->ptr, x, y, 0x007700);
	}
	redraw_fract_or_img(env, 1);
}
