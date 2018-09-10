/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 19:23:35 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/10 11:30:39 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		if_сardioid(t_env *env, double pr, double pi)
{
	double		pr_pow;
	double		pi_pow;
	double		q;
	t_flags		*flags;

	if (!env
		|| env->param->fr_id == FR_JULIA
		|| !(flags = env->flags)
		|| flags->n1 || flags->n2 || flags->n3 || flags->n7)
		return (0);
	pr_pow = ((pr - 0.25) * (pr - 0.25));
	pi_pow = pi * pi;
	q = pr_pow + pi_pow;
	if ((pr + 1) * (pr + 1) + pi_pow < 0.0625
		|| (q * (q + (pr - 0.25)) < 0.25 * pi_pow))
		return (1);
	return (0);
}

int		mandel_break(t_env *env, t_cnb *z)
{
	t_flags	*f;

	z->rsq = pow2(z->r, 2);
	z->isq = pow2(z->i, 2);
	f = env->flags;
	if (f->n8 && z->rsq * z->isq > env->param->spec1)
		return (1);
	if (f->n4 && z->rsq - z->isq > env->param->spec1)
		return (1);
	if (!f->n8 && !f->n4 && z->rsq + z->isq > env->param->spec1)
		return (1);
	if (env->flags->n5 && (z->r > 0.5 || z->r < -2.0))
		return (1);
	if (env->flags->n5 && (z->i > 0.8 || z->i < -0.8))
		return (1);
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
