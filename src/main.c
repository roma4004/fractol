/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/10 15:50:34 by dromanic         ###   ########.fr       */
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

void		show_errors(t_env *env)
{
	if (env->flags->error_code == 404)
		ft_putstr_fd("MAP_INVALID", 2);
	if (env->flags->error_code == 405)
		ft_putstr_fd("WIDTH_ERR", 2);
	if (env->flags->error_code == 406)
		ft_putstr_fd("FILE_ERR", 2);
	if (env->flags->error_code == 407)
		ft_putstr_fd("COLOR_ERR", 2);
	if (env->flags->error_code && errno)
		ft_putstr_fd(" - ", 2);
	if (errno)
		ft_putstr_fd(strerror(errno), 2);
	if (env->flags->error_code || errno)
		ft_putstr_fd("\n", 2);
}

int		main(void)//int argc, char **argv)
{
	t_env *win;

	win = init_win();
	//if (argc > 1 && (win = init_win()))
	//{
	//	if (parse_map(argv[1], win))
	//	{
	//init_mandelbrot(win->param);
	win->init_func[FR_MANDELBROT](win->param);
	redraw_fract(win, 0);
	//parallel_draw_fractal(win);
	mlx_hook(win->win_ptr, 17, 1L << 17, exit_x, win);
	mlx_hook(win->win_ptr, 2, 5, deal_keyboard, win);
	mlx_hook(win->win_ptr, 6, 8, deal_mouse_move, win);
	mlx_mouse_hook(win->win_ptr, deal_mouse, win);
	mlx_loop(win->mlx_ptr);
	//	}
	//}

	/*
	if (argc == 2 && (win = init_win()))
	{
		if (parse_map(argv[1], win))
		{
			draw_map(win);
			mlx_hook(win->win_ptr, 17, 1L << 17, exit_x, win);
			mlx_hook(win->win_ptr, 2, 5, deal_keyboard, win);
			mlx_mouse_hook(win->win_ptr, deal_mouse, win);
			mlx_loop(win->mlx_ptr);
		}
		else
		{
			show_errors(win);
			exit_x(win);
		}
	}
	else
	{
		ft_putstr("Usage: ./fdf map.fdf\n");
		exit(1);
	}*/
	show_errors(win);
	return (0);
}
