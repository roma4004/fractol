/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/12 18:02:07 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			if_сardioid(t_env *env, double pr, double pi)
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

int			mandel_break(t_env *env, t_cnb *z)
{
	t_flags	*f;

	z->rsq = ft_pow(z->r, 2);
	z->isq = ft_pow(z->i, 2);
	f = env->flags;
	if (f->n8 && z->rsq * z->isq > env->param->spec1)
		return (1);
	if (f->n4 && z->rsq - z->isq > env->param->spec1)
		return (1);
	if (!f->n8 && !f->n4 && z->rsq + z->isq > env->param->spec1)
		return (1);
	if (env->flags->n5
	&& (z->r > env->param->right_trim * env->param->spec2
		|| z->r < env->param->left_trim * env->param->spec2))
		return (1);
	if (env->flags->n5
	&& (z->i > env->param->down_trim * env->param->spec2
		|| z->i < env->param->up_trim * env->param->spec2))
		return (1);
	return (0);
}

static int	set_fract(t_env *env, char *name)
{
	env->param->fr_id = -1;
	if (((ft_strcmp(name, "Barnsley")) == 0)
	|| (ft_strcmp(name, "B")) == 0)
		env->param->fr_id = FR_BARNSLEY;
	else if (((ft_strcmp(name, "Mandelbrot")) == 0)
	|| (ft_strcmp(name, "M")) == 0)
		env->param->fr_id = FR_MANDELBROT;
	else if (((ft_strcmp(name, "Batman")) == 0)
	|| (ft_strcmp(name, "BM")) == 0)
		env->param->fr_id = FR_BATMAN;
	else if (((ft_strcmp(name, "Mandelbrot_cuboid")) == 0)
	|| (ft_strcmp(name, "MC")) == 0)
		env->param->fr_id = FR_MANDELBROT_CUBOID;
	else if (((ft_strcmp(name, "Julia")) == 0)
	|| (ft_strcmp(name, "J")) == 0)
		env->param->fr_id = FR_JULIA;
	if (env->param->fr_id == -1)
		return (1);
	env->init_func[env->param->fr_id](env->param);
	return (0);
}

int			main(int argc, char **argv)
{
	t_env	*env;

	if (argc == 2 && (env = init_win()) && !set_fract(env, argv[1]))
	{
		redraw_fract(env, 0);
		mlx_hook(env->win_ptr, 17, 1L << 17, exit_x, env);
		mlx_hook(env->win_ptr, 2, 5, deal_keyboard, env);
		mlx_hook(env->win_ptr, 6, 8, deal_mouse_move, env);
		mlx_mouse_hook(env->win_ptr, deal_mouse, env);
		mlx_loop(env->mlx_ptr);
	}
	else
	{
		ft_putstr("Usage: ./fractol [ Mandelbrot | M | Julia | J | Barnsley | B"
					" | Mandelbrot_cuboid | MC | Batman | BM ]\n");
		exit(1);
	}
	return (0);
}
