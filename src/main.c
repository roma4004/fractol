/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/16 17:40:50 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			is_cardioid(t_param *param, t_flags *flags, t_cnb *z)
{
	double		q;

	if (!param || !flags || flags->n1 || flags->n2 || flags->n3 || flags->n7)
		return (0);
	z->rsq = ((z->rc - 0.25) * (z->rc - 0.25));
	z->isq = z->ic * z->ic;
	q = z->rsq + z->isq;
	if ((z->rc + 1) * (z->rc + 1) + z->isq < 0.0625
		|| (q * (q + (z->rc - 0.25)) < 0.25 * z->isq))
		return (1);
	return (0);
}

int			mandel_break(t_param *param, t_flags *flags, t_cnb *z)
{
	z->rsq = ft_pow(z->r, 2);
	z->isq = ft_pow(z->i, 2);
	if (flags->n8 && z->rsq * z->isq > param->spec1)
		return (1);
	if (flags->n4 && z->rsq - z->isq > param->spec1)
		return (1);
	if (!flags->n8 && !flags->n4 && z->rsq + z->isq > param->spec1)
		return (1);
	if (flags->n5 && (z->r > param->right_trim * param->spec2
					|| z->r < param->left_trim * param->spec2))
		return (1);
	if (flags->n5 && (z->i > param->down_trim * param->spec2
					|| z->i < param->up_trim * param->spec2))
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

	if (argc == 2 && (env = init_env()) && !set_fract(env, argv[1]))
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
