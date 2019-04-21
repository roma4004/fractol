/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/21 20:51:01 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static unsigned int		change_hue(unsigned *color, int is_increase,
									unsigned char color_bit_shift)
{
	unsigned int	mask;
	unsigned int	increment;

	mask = 0x000000FFU << color_bit_shift;
	increment = mask & 0x01010101U;
	*color += (is_increase == 1) ? increment : -increment;
	return (*color);
}

static unsigned int		shift_apply(t_env *env, int is_increase,
									unsigned char chanel)
{
	size_t		y;
	size_t		x;

	y = UINT64_MAX;
	while (W_HEIGHT > ++y)
	{
		x = UINT64_MAX;
		while (W_WIDTH > ++x)
			change_hue(&env->surface[y * W_WIDTH + x], is_increase, chanel);
	}
	return (redraw_fract_or_img(env, env->param, env->flags, 1));
}

unsigned int			change_color(t_env *env, t_col_shift *col_shift,
										int key)
{
	int				is_increase;
	unsigned char	chanel;

	if (!env)
		return (0);
	is_increase = 0;
	if ((key == A || key == Z)
	&& (chanel = ALPHA))
		col_shift->alpha +=
			(is_increase = (key == A) ? 1 : -1);
	else if ((key == S || key == X)
	&& (chanel = RED))
		col_shift->red +=
			(is_increase = (key == S) ? 1 : -1);
	else if ((key == D || key == C)
	&& (chanel = GREEN))
		col_shift->green +=
			(is_increase = (key == D) ? 1 : -1);
	else if ((key == F || key == V)
	&& !(chanel = BLUE))
		col_shift->blue +=
			(is_increase = (key == F) ? 1 : -1);
	if (is_increase != 0 && shift_apply(env, is_increase, chanel))
		return (1);
	return (0);
}

void					argb_shift(t_env *env, t_col_shift shift)
{
	int		i_cur;
	int		i_max;
	int		is_increase;

	i_max = (shift.alpha >= 0) ? shift.alpha : 0;
	i_cur = (shift.alpha >= 0) ? -1 : shift.alpha - 1;
	is_increase = (shift.alpha >= 0) ? 1 : -1;
	while (++i_cur < i_max)
		shift_apply(env, is_increase, ALPHA);
	i_max = (shift.red >= 0) ? shift.red : 0;
	i_cur = (shift.red >= 0) ? -1 : shift.red - 1;
	is_increase = (shift.red >= 0) ? 1 : -1;
	while (++i_cur < i_max)
		shift_apply(env, is_increase, RED);
	i_max = (shift.green >= 0) ? shift.green : 0;
	i_cur = (shift.green >= 0) ? -1 : shift.green - 1;
	is_increase = (shift.green >= 0) ? 1 : -1;
	while (++i_cur < i_max)
		shift_apply(env, is_increase, GREEN);
	i_max = (shift.blue >= 0) ? shift.blue : 0;
	i_cur = (shift.blue >= 0) ? -1 : shift.blue - 1;
	is_increase = (shift.blue >= 0) ? 1 : -1;
	while (++i_cur < i_max)
		shift_apply(env, is_increase, BLUE);
}

unsigned int			get_color(bool alt_col, double col_step,
									unsigned int depth, unsigned int i)
{
	unsigned int	color;
	double			step;
	t_color			col;

	if (!alt_col)
	{
		color = (unsigned int)(col_step * i);
		return (color);
	}
	step = (double)i / (double)depth;
	col = (t_color){ 0,
			(unsigned int)(9 * (1 - step) * step * step * 255),
			(unsigned int)(15 * (1 - step) * (1 - step) * step * 255),
			(unsigned int)(8.5 * (1 - step) * (1 - step) * (1 - step) * 255) };
	return ((col.a << 24U) | ((col.r) << 16U) | ((col.g) << 8U) | (col.b));
}
