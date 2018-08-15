/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/15 19:55:14 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void show_errors(t_win *win)
{
	if (win->flags->error_code == 404)
		ft_putstr_fd("MAP_INVALID", 2);
	if (win->flags->error_code == 405)
		ft_putstr_fd("WIDTH_ERR", 2);
	if (win->flags->error_code == 406)
		ft_putstr_fd("FILE_ERR", 2);
	if (win->flags->error_code == 407)
		ft_putstr_fd("COLOR_ERR", 2);
	if (win->flags->error_code && errno)
		ft_putstr_fd(" - ", 2);
	if (errno)
		ft_putstr_fd(strerror(errno), 2);
	if (win->flags->error_code || errno)
		ft_putstr_fd("\n", 2);
}

void	draw_fractal(t_win *win)
{
	int i;
	int y;
	int x;
	y = -1;
//	t_cnb   c;

	while(y++ < WIN_HEIGHT)
	{
		x = 0;
		while (x++ < WIN_WIDTH)
		{
			i = get_fractal_point(win, x, y);
			//use color model conversion to get rainbow palette, make brightness black if maxIterations reached
			//color = HSVtoRGB(ColorHSV(i % 256, 255, 255 * (i < maxIterations)));

			win->param->color = win->param->color_step * (i);//+ 1114112;
			//win->param->color =(i *(x+y) / win->param->iter) * (newRe * newIm);
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, win->param->color);
			//mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y, win->param->color);
		}
	}
}


void	change_fract(t_win *win, int fr_new_type)
{
	win->param->fr_id = fr_new_type;
	init_fract(win);
	redraw_fract(win);
}

int main(void)//int argc, char **argv)
{
	t_win *win;
	win = init_win();
	//if (argc > 1 && (win = init_win()))
	//{
	//	if (parse_map(argv[1], win))
	//	{
			change_fract(win, FR_MANDELBROT);
			redraw_fract(win);
			mlx_hook(win->win_ptr, 17, 1L << 17, exit_x, win);
			mlx_hook(win->win_ptr, 2, 5, deal_keyboard, win);
			mlx_mouse_hook(win->win_ptr, deal_mouse, win);
			mlx_loop(win->mlx_ptr);
	//	}
	//}

	/*t_win	*win;

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
99		exit(1);
	}*/
	show_errors(win);
	return (0);
}
