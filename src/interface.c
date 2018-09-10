/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:48:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/10 17:31:14 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	disp(t_env *env, int x, int y, char *str)
{
	mlx_string_put(env->mlx_ptr, env->win_ptr, x, y,
				(env->flags->green_text) ? 0x00ff00 : DEF_COLOR, str);
	if (env->flags->green_text)
		toggle_flag(&env->flags->green_text);
}

static void	disp_green(t_env *env, int x, int y, char *str)
{
	mlx_string_put(env->mlx_ptr, env->win_ptr, x, y, 0x00ff00, str);
	if (env->flags->green_text)
		toggle_flag(&env->flags->green_text);
}

void		show_values(t_env *e, int x, int y)
{
	x += ((e->flags->menu_on) ? 550 : 0) + ((e->flags->hints_on) ? 450 : 0);
	disp(e, x, y, "ACTUAL VALUES:");
	disp(e, x, y += 20, "iter_max       :");
	disp(e, x + 170, y, ft_itoa(e->param->iter_max));
	disp(e, x, y += 20, "zoom           :");
	disp(e, x + 170, y, ft_itoa(e->param->zoom));
	disp(e, x, y += 20, "color step     :");
	disp(e, x + 170, y, ft_itoa(e->param->iter_step));
	disp(e, x, y += 20, "threads        :");
	disp(e, x + 170, y, ft_itoa(e->param->cpu_cores));
}

void		show_combo(t_env *env, int x, int y)
{
	x += ((env->flags->menu_on) ? 550 : 0);
	disp(env, x, y, "COMBO HINT:");
	disp(env, x, y += 20, "background: r + q + e");
	disp(env, x, y += 20, "wind      : r + q or r + e");
	disp(env, x, y += 20, "flower    : r + 8 or num_8");
	disp(env, x, y += 20, "leaf      : r + 4 or num_4");
	disp(env, x, y += 20, "clouds    : r + 4 or num_4 + 8 or num_8");
	disp(env, x, y += 20, "blades    : r + 4 + Z (press Z 17 times)");
	disp(env, x, y += 20, "burn ship : r + 2 + 3 (for Mandelbrot)");
	disp(env, x, y += 20, "tricorn   : r + 2 (for Mandelbrot)");
	disp(env, x, y += 20, "lohnes    : r + q, e, t)");
	disp(env, x, y += 20, "heart     : r + 3 or num_3");
	disp(env, x, y += 20, "mirror hor: 6 or num_6");
	disp(env, x, y += 20, "mirror ver: 7 or num_7 (for Ship, Lohnes)");
}

void		show_menu(t_env *e, int x, int y, t_flags *f)
{
	disp(e, x, y, "zoom         : -, + or mouse scroll");
	disp(e, x, y += 20, "Enter        : next fractal");
	disp(e, x, y += 20, "interface    : num_0");
	disp(e, x, y += 20, "depth        : num_+, num_- or 9, 0");
	disp(e, x, y += 20, "depth step   : num_/, num_*");
	disp(e, x, y += 20, "reset        : R");
	disp(e, x, y += 20, "effects      : 1..8 or num_1..num_8");
	(f->q) ? disp_green(e, x + 360, y, "Q") : disp(e, x + 360, y, "Q");
	(f->e) ? disp_green(e, x + 380, y, "E") : disp(e, x + 380, y, "E");
	disp(e, x, y += 20, "calc carioid :");
	(f->if_carioid) ? disp_green(e, x + 150, y, "Y") : disp(e, x + 150, y, "Y");
	disp(e, x, y += 20, "white carioid:   (when calk carioid is on)");
	(f->w) ? disp_green(e, x + 150, y, "W") : disp(e, x + 150, y, "W");
	disp(e, x, y += 20, "color style  :  ,   ");
	(f->col_range) ? disp_green(e, x + 150, y, "T") : disp(e, x + 150, y, "T");
	(f->alt_color) ? disp_green(e, x + 180, y, "G") : disp(e, x + 180, y, "G");
	disp(e, x, y += 20, "mouse detect : mouse_");
	(f->lock_julia) ? disp_green(e, x + 210, y, "R") : disp(e, x + 210, y, "R");
	disp(e, x, y += 20, "shift ARGB   : (+,-)   A,Z   S,X   D,C   F,V");
	disp(e, x, y += 20, "radius change: Home, End");
	disp(e, x, y += 20, "curve X      : Home, End (for Barnsley)");
	disp(e, x, y += 20, "curve Y      : Page_Up, Page_Down (for Barnsley)");
	disp(e, x, y += 20, "menu         : M");
	disp(e, x, y += 20, "combo        : H");
	disp(e, x, y += 20, "values       : N");
}
