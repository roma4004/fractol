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

static void				change_hue(unsigned *restrict color, int is_increase,
									unsigned char color_bit_shift)
{
	unsigned int	mask;
	unsigned int	increment;

	mask = 0x000000FFU << color_bit_shift;
	increment = mask & 0x01010101U;
	*color += (1 == is_increase) ? increment : -increment;
}

static unsigned int		shift_apply(t_env *restrict env, int is_increase,
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

unsigned int			change_color(t_env *restrict env,
									t_col_shift *restrict col_shift, int key)
{
	int				is_increase;
	unsigned char	chanel;

	if (!env)
		return (0);
	is_increase = 0;
	if ((A == key || Z == key)
	&& (chanel = ALPHA))
		col_shift->alpha +=
			(is_increase = (A == key) ? 1 : -1);
	else if ((S == key || X == key)
	&& (chanel = RED))
		col_shift->red +=
			(is_increase = (S == key) ? 1 : -1);
	else if ((D == key || C == key)
	&& (chanel = GREEN))
		col_shift->green +=
			(is_increase = (D == key) ? 1 : -1);
	else if ((F == key || V == key)
	&& !(chanel = BLUE))
		col_shift->blue +=
			(is_increase = (F == key) ? 1 : -1);
	if (is_increase != 0 && shift_apply(env, is_increase, chanel))
		return (1);
	return (0);
}

void					argb_shift(t_env *restrict env, t_col_shift shift)
{
	int		i_cur;
	int		i_max;
	int		is_increase;

	i_max = (0 <= shift.alpha) ? shift.alpha : 0;
	i_cur = (0 <= shift.alpha) ? -1 : shift.alpha - 1;
	is_increase = (0 <= shift.alpha) ? 1 : -1;
	while (i_max > ++i_cur)
		shift_apply(env, is_increase, ALPHA);
	i_max = (0 <= shift.red) ? shift.red : 0;
	i_cur = (0 <= shift.red) ? -1 : shift.red - 1;
	is_increase = (0 <= shift.red) ? 1 : -1;
	while (i_max > ++i_cur)
		shift_apply(env, is_increase, RED);
	i_max = (0 <= shift.green) ? shift.green : 0;
	i_cur = (0 <= shift.green) ? -1 : shift.green - 1;
	is_increase = (0 <= shift.green) ? 1 : -1;
	while (i_max > ++i_cur)
		shift_apply(env, is_increase, GREEN);
	i_max = (0 <= shift.blue) ? shift.blue : 0;
	i_cur = (0 <= shift.blue) ? -1 : shift.blue - 1;
	is_increase = (0 <= shift.blue) ? 1 : -1;
	while (i_max > ++i_cur)
		shift_apply(env, is_increase, BLUE);
}

unsigned int			get_color(bool alt_col, double col_step,
									unsigned int depth, unsigned int i)
{
	double			step;
	t_color			col;

	if (!alt_col)
		return ((unsigned int)(col_step * i));
	step = (double)i / (double)depth;
	col = (t_color){ 0,
			(unsigned int)(9 * (1 - step) * step * step * 255),
			(unsigned int)(15 * (1 - step) * (1 - step) * step * 255),
			(unsigned int)(8.5 * (1 - step) * (1 - step) * (1 - step) * 255) };
	return ((col.a << 24U) | ((col.r) << 16U) | ((col.g) << 8U) | (col.b));
}
