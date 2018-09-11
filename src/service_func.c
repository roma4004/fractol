/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 19:23:35 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/11 21:03:20 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		text(t_env *env, int x, int y, char *str)
{
	if (env && str)
	{
		mlx_string_put(env->mlx_ptr, env->win_ptr, x, y,
				(env->flags->green_text) ? 0x00ff00 : DEF_COLOR, str);
		if (env->flags->green_text)
			env->flags->green_text = ~env->flags->green_text;
		return (1);
	}
	return (0);
}

int		text_green(t_env *env, int x, int y, char *str)
{
	if (env && str)
	{
		mlx_string_put(env->mlx_ptr, env->win_ptr, x, y, 0x00ff00, str);
		if (env->flags->green_text)
			env->flags->green_text = ~env->flags->green_text;
		return (1);
	}
	return (0);
}

double	pow2(double num, int exp)
{
	double	result;

	result = 1.0;
	while (exp > 0)
	{
		if (exp % 2 == 1)
			result *= num;
		exp >>= 1;
		num *= num;
	}
	return (result);
}

int		get_processors_num(void)
{
	int		nm[2];
	int		count;
	size_t	len;

	len = 4;
	nm[0] = CTL_HW;
	nm[1] = HW_AVAILCPU;
	sysctl(nm, 2, &count, &len, NULL, 0);
	if (count < 1)
	{
		nm[1] = HW_NCPU;
		sysctl(nm, 2, &count, &len, NULL, 0);
		if (count < 1)
			count = 1;
	}
	return ((ALMOST_HYPER_THREADING) ? (count * 2) : count);
}
