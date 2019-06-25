/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2019/06/25 19:08:34 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				is_cardioid(t_flags flags, t_cnb *restrict z)
{
	double		q;

	if (flags.n1 || flags.n2 || flags.n3 || flags.n7)
		return (0);
	z->rsq = (z->rc - 0.25) * (z->rc - 0.25);
	z->isq = z->ic * z->ic;
	q = z->rsq + z->isq;
	if ((((z->rc + 1) * (z->rc + 1) + z->isq) < 0.0625)
	|| (q * (q + z->rc - 0.25) < 0.25 * z->isq))
		return (1);
	return (0);
}

int				mandel_break(t_param p, t_flags flags, t_cnb *restrict z)
{
	z->rsq = ft_pow(z->r, 2);
	z->isq = ft_pow(z->i, 2);
	if ((flags.n9 && ((unsigned int)(z->isq) & (unsigned int)(z->rsq)) > p.hor)
	|| (flags.n8 && z->rsq * z->isq > p.hor)
	|| (!flags.n9 && flags.n4 && z->rsq - z->isq > p.hor)
	|| (flags.n9 && flags.n4 && z->rsq - z->isq > p.hor)
	|| (!flags.n9 && !flags.n8 && !flags.n4 && z->rsq + z->isq > p.hor)
	|| (flags.n5 && (z->r > p.trim.right * p.ver || z->r < p.trim.left * p.ver
					|| z->i > p.trim.down * p.ver || z->i < p.trim.up * p.ver)))
		return (1);
	return (0);
}

static int		set_fract(t_env *restrict env, t_param *restrict param,
							char *name)
{
	const size_t	len = ft_strlen(name);
	unsigned int	id;

	id = UINT32_MAX;
	while (AMOUNT_FRACTALS > ++id)
	{
		if (((unsigned int)ft_atoi(name) == id + 1)
		|| !ft_strncmp(name, env->fract_names[id], len))
		{
			param->fr_id = id;
			env->init_func[id](&env->param);
			return (1);
		}
	}
	return (0);
}

unsigned int	redraw_fract_or_img(t_env const *restrict env, t_param param,
									t_flags flags, int img_only)
{
	t_ui_pt		pt;

	if (!img_only)
	{
//		if (FR_FERN == param.fr_id && (pt.y = UINT32_MAX))
//		{
//			while (W_HEIGHT > ++(pt.y) && (pt.x = UINT32_MAX))
//				while (W_WIDTH > ++(pt.x))
//					env->surf[pt.y * W_WIDTH + pt.x] = 0;
//			return (draw_barnsley(env, param, 0, 0));
//		}
		parallel_draw(env, param.threads);
	}
	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img_ptr, 0, 0);
	if (!flags.menu)
		show_menu(env, flags, 20, 10);
	if (!flags.hints)
		show_combo(env, flags.menu, 20, 10);
	if (!flags.values)
		show_values(env, param, 20, 10);
	return (1);
}

int				main(int argc, char **argv)
{
	t_env	env;

	if (argc == 2 && (init_env(&env)) && set_fract(&env, &env.param, argv[1]))
	{
		redraw_fract_or_img(&env, env.param, env.flags, 0);
		mlx_hook(env.win_ptr, 17, 1, exit_x, &env);
		mlx_hook(env.win_ptr, 2, 5, deal_keyboard, &env);
		mlx_hook(env.win_ptr, 6, 8, deal_mouse_move, &env);
		mlx_mouse_hook(env.win_ptr, deal_mouse, &env);
		mlx_loop(env.mlx_ptr);
	}
	else
	{
		ft_putstr("Usage: ./fractol [ 1 | M | Mandelbrot\n"
				"                 | 2 | J | Julia\n"
				"                 | 3 | F | Fern\n"
				"                 | 4 | C | Cuboid\n"
				"                 | 5 | B | Batman ]\n"
		"examples:\n"
		"    to show Mandelbrot set use the index number \"./fractol 1\"\n"
		"    or first letter of fractal \"./fractol M\"\n"
		"    or full name as argument \"./fractol Mandelbrot\"\n\n");
		exit(1);
	}
	return (0);
}
