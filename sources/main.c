/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/12/25 19:00:32 by dromanic         ###   ########.fr       */
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
	if (flags->n5 && (z->r > param->trim.right * param->spec2
					|| z->r < param->trim.left * param->spec2))
		return (1);
	if (flags->n5 && (z->i > param->trim.down * param->spec2
					|| z->i < param->trim.up * param->spec2))
		return (1);
	return (0);
}

static int	set_fract(t_env *env, t_param *param, char *name)
{
	size_t	len;

	len = ft_strlen(name);
	param->fr_id = -1;
	while (++param->fr_id < AMOUNT_FRACTALS)
	{
		if ((ft_atoi(name) == param->fr_id + 1)
		|| !ft_strncmp(name, env->names[param->fr_id], len))
		{
			env->init_func[param->fr_id](param);
			return (1);
		}
	}
	return (0);
}

void		redraw_fract_or_img(t_env *env, t_param *param, int img_only)
{
	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img->ptr, 0, 0);
	if (!env->flags->menu)
		show_menu(env, env->flags, 20, 10);
	if (!env->flags->hints)
		show_combo(env, 20, 10);
	if (!env->flags->values)
		show_values(env, param, 0, 20);
	if (img_only)
		return ;
	if (param->fr_id == FR_FERN && clear_img(env))
		draw_barnsley(env, (t_int_pt){0, 0});
	else
		parallel_draw(env, param->threads);
}

int			main(int argc, char **argv)
{
	t_env	*env;

	if (argc == 2 && (env = init_env()) && set_fract(env, env->param, argv[1]))
	{
		redraw_fract_or_img(env, env->param, 0);
		mlx_hook(env->win_ptr, 17, 1L << 17, exit_x, env);
		mlx_hook(env->win_ptr, 2, 5, deal_keyboard, env);
		mlx_hook(env->win_ptr, 6, 8, deal_mouse_move, env);
		mlx_mouse_hook(env->win_ptr, deal_mouse, env);
		mlx_loop(env->mlx_ptr);
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
