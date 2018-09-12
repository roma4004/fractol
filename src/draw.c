/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/12 18:59:54 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		redraw_fract(t_env *env, int img_only)
{
	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr,
							env->img->ptr, 0, 0);
	if (env->flags->menu_on)
		show_menu(env, 20, 10, env->flags);
	if (env->flags->hints_on)
		show_combo(env, 20, 10);
	if (env->flags->values_on)
		show_values(env, 20, 10);
	if (img_only)
		return ;
	if (env->param->fr_id == FR_BARNSLEY)
		draw_barnsley(clear_img(env));
	else
		parallel_draw_fractal(env);
}

int			get_fractal_col(t_env *env, int x, int y)
{
	if (env->param->fr_id == FR_JULIA)
		return (get_julia_color(env, x, y));
	if (env->param->fr_id == FR_BATMAN)
		return (get_batman_color(env, x, y));
	if (env->param->fr_id == FR_MANDELBROT)
		return (get_mandelbrot_color(env, x, y));
	if (env->param->fr_id == FR_MANDELBROT_CUBOID)
		return (get_mandelbrot_cuboid_color(env, x, y));
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

void		draw_barnsley(t_env *env)
{
	float		rng;
	long		n;
	t_coords	i;
	t_cnb		c;
	t_param		*par;

	c = (t_cnb){.r = 0, .i = 0};
	par = env->param;
	n = par->i_max;
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
		i.x = (int)((c.r + 4) * par->zoom - par->offset_x);
		i.y = (int)(WIN_HEIGHT - c.i * par->zoom - par->offset_y);
		px_to_img(env->img->ptr, i.x, i.y, 0x007700);
	}
	redraw_fract(env, 1);
}
