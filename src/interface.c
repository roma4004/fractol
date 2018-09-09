/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:48:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/09 20:15:22 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	disp(t_env *env, int x, int y, char *str)
{
	mlx_string_put(env->mlx_ptr, env->win_ptr, x, y, DEF_COLOR, str);
}

void		show_value(t_env *env, int x, int y)
{
	x += 20 + ((env->flags->Menu_on) ? 550 : 0)
		+ ((env->flags->Hints_on) ? 450 : 0);
	y += 10;
	disp(env, x, y, "ACTUAL VALUES:");
	disp(env, x, y += 20, "iter         :");
	disp(env, x + 150, y, ft_itoa(env->param->iter));
	disp(env, x, y += 20, "zoom         :");
	disp(env, x + 150, y, ft_itoa(env->param->zoom));
	disp(env, x, y += 20, "color step   :");
	disp(env, x + 150, y, ft_itoa(env->param->iter_step));
	disp(env, x, y += 20, "CPU num      : R + 4 or num_4");
	disp(env, x + 190, y, ft_itoa(env->param->cpu_cores));
	disp(env, x, y += 20, "blades       : R + 4 + Z (press Z 17 times)");
	disp(env, x, y += 20, "burn ship    : R + 2 + 3 (only Mandelbrot)");
	disp(env, x, y += 20, "tricorn      : R + 2 (only Mandelbrot)");
	disp(env, x, y += 20, "lohnes       : R + Q, E, T)");
	disp(env, x, y += 20, "heard        : R + 3 or num_3");
	disp(env, x, y += 20, "mirror horiz : 6 or num_6");
	disp(env, x, y += 20, "mirror vertic: 7 or num_7 (only ship, lohnes)");
}

void		show_combo(t_env *env, int x, int y)
{
	x = 20 + ((env->flags->Menu_on) ? 550 : 0);
	y = 10;
	disp(env, x, y, "COMBO HINT:");
	disp(env, x, y += 20, "background: R + Q + E");
	disp(env, x, y += 20, "wind      : R + Q or R + E");
	disp(env, x, y += 20, "flower    : R + 8 or num_8");
	disp(env, x, y += 20, "leaf      : R + 4 or num_4");
	disp(env, x, y += 20, "clouds    : R + 4 or num_4 + 8 or num_8");
	disp(env, x, y += 20, "blades    : R + 4 + Z (press Z 17 times)");
	disp(env, x, y += 20, "burn ship : R + 2 + 3 (only Mandelbrot)");
	disp(env, x, y += 20, "tricorn   : R + 2 (only Mandelbrot)");
	disp(env, x, y += 20, "lohnes    : R + Q, E, T)");
	disp(env, x, y += 20, "heard     : R + 3 or num_3");
	disp(env, x, y += 20, "mirror hor: 6 or num_6");
	disp(env, x, y += 20, "mirror ver: 7 or num_7 (only ship, lohnes)");
}

void		show_menu(t_env *env, int x, int y)
{
	x = 20;
	y = 10;
	disp(env, x, y, "MENU         :");
	disp(env, x, y += 20, "zoom         : -, + or mouse scroll");
	disp(env, x, y += 20, "zoom         : -, + or mouse scroll");
	disp(env, x, y += 20, "Enter        : next fractal");
	disp(env, x, y += 20, "interface    : num_0");
	disp(env, x, y += 20, "depth        : num_+, num_- or 9, 0");
	disp(env, x, y += 20, "depth step   : num_/, num_*");
	disp(env, x, y += 20, "reset        : R");
	disp(env, x, y += 20, "effects      : 1..8 or num_1..num_8, Q, E ");
	disp(env, x, y += 20, "carioid skip : Y");
	disp(env, x, y += 20, "carioid color: W (black or white))");
	disp(env, x, y += 20, "color style  : T, G");
	disp(env, x, y += 20, "shift ARGB   : (+,-)   A,Z   S,X   D,C   F,V");
	disp(env, x, y += 20, "radius change: Home, End");
	disp(env, x, y += 20, "curve X      : Home, End (only barnsley)");
	disp(env, x, y += 20, "curve Y      : Page_Up, Page_Down (only barnsley)");
	disp(env, x, y += 20, "menu         : M");
	disp(env, x, y += 20, "combo        : H");
	disp(env, x, y += 20, "values       : N");
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
