/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/09 21:14:56 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	redraw_fract(win);
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
