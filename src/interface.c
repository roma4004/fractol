/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:48:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/11 17:55:56 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		show_values(t_env *e, int x, int y)
{
	x += ((e->flags->menu_on) ? 550 : 0) + ((e->flags->hints_on) ? 450 : 0);
	text(e, x, y, "ACTUAL VALUES:");
	text(e, x, y += 20, "current fractal: ");
	(e->param->fr_id == 0) && (text(e, x + 170, y, "Barnsley"));
	(e->param->fr_id == 1) && (text(e, x + 170, y, "Mandelbrot"));
	(e->param->fr_id == 2) && (text(e, x + 170, y, "Batman"));
	(e->param->fr_id == 3) && (text(e, x + 170, y, "Mandelbrot cuboid"));
	(e->param->fr_id == 4) && (text(e, x + 170, y, "Julia"));
	text(e, x, y += 20, "iteration limit:");
	text(e, x + 170, y, ft_lltoa(e->param->iter_max));
	text(e, x, y += 20, "iteration step :");
	text(e, x + 170, y, ft_lltoa(e->param->iter_step));
	text(e, x, y += 20, "zoom           :");
	text(e, x + 170, y, ft_lltoa(e->param->zoom));
	text(e, x, y += 20, "threads        :");
	text(e, x + 170, y, ft_lltoa(e->param->cpu_cores));
	text(e, x, y += 20, "shift alpha    :");
	text(e, x + 170, y, ft_lltoa(e->param->alpha_shift_iter));
	text(e, x, y += 20, "shift red      :");
	text(e, x + 170, y, ft_lltoa(e->param->red_shift_iter));
	text(e, x, y += 20, "shift green    :");
	text(e, x + 170, y, ft_lltoa(e->param->green_shift_iter));
	text(e, x, y += 20, "shift blue     :");
	text(e, x + 170, y, ft_lltoa(e->param->blue_shift_iter));
}

void		show_combo(t_env *env, int x, int y)
{
	x += ((env->flags->menu_on) ? 550 : 0);
	text(env, x, y, "COMBO HINT:");
	text(env, x, y += 20, "background: r + q + e");
	text(env, x, y += 20, "wind      : r + q, r + e");
	text(env, x, y += 20, "leaf      : r + 4 or num_4");
	text(env, x, y += 20, "flower    : r + 8 or num_8");
	text(env, x, y += 20, "clouds    : r + 4 or num_4 + 8 or num_8");
	text(env, x, y += 20, "blades    : r + 4 + Z (press Z 17 times)");
	text(env, x, y += 20, "burn ship : r + 2 + 3 (for Mandelbrot)");
	text(env, x, y += 20, "tricorn   : r + 2 (for Mandelbrot)");
	text(env, x, y += 20, "lohnes    : r + q, e, t)");
	text(env, x, y += 20, "heart     : r + 3 or num_3");
	text(env, x, y += 20, "mirror hor: 6 or num_6");
	text(env, x, y += 20, "mirror ver: 7 or num_7 (for Ship, Lohnes)");
}

static void	show_menu2(t_env *e, int x, int y, t_flags *f)
{
	text(e, x, y += 20, "calc carioid :");
	(f->if_carioid) ? text_green(e, x + 150, y, "Y") : text(e, x + 150, y, "Y");
	text(e, x, y += 20, "white carioid:   (when calk carioid is on)");
	(f->w) ? text_green(e, x + 150, y, "W") : text(e, x + 150, y, "W");
	text(e, x, y += 20, "color style  :  ,   ");
	(f->col_range) ? text_green(e, x + 150, y, "T") : text(e, x + 150, y, "T");
	(f->alt_color) ? text_green(e, x + 180, y, "G") : text(e, x + 180, y, "G");
	text(e, x, y += 20, "mouse detect : mouse_");
	(f->lock_julia) ? text_green(e, x + 210, y, "R") : text(e, x + 210, y, "R");
	text(e, x, y += 20, "shift ARGB   : (+,-)   A,Z   S,X   D,C   F,V");
	text(e, x, y += 20, "radius change: Home, End");
	text(e, x, y += 20, "curve X      : Home, End (for Barnsley)");
	text(e, x, y += 20, "curve Y      : Page_Up, Page_Down (for Barnsley)");
	text(e, x, y += 20, "menu         : M");
	text(e, x, y += 20, "combo        : H");
	text(e, x, y += 20, "values       : N");
}

void		show_menu(t_env *e, int x, int y, t_flags *f)
{
	text(e, x, y, "MENU         :");
	text(e, x, y += 20, "zoom         : -, + or mouse scroll");
	text(e, x, y += 20, "next fractal : Enter");
	text(e, x, y += 20, "depth        : num_+, num_- or 9, 0");
	text(e, x, y += 20, "depth step   : num_/, num_*");
	text(e, x, y += 20, "reset        : R");
	text(e, x, y += 20, "effects      :                 (or numpad)");
	(f->n1) ? text_green(e, x + 150, y, "1") : text(e, x + 150, y, "1");
	(f->n2) ? text_green(e, x + 170, y, "2") : text(e, x + 170, y, "2");
	(f->n3) ? text_green(e, x + 190, y, "3") : text(e, x + 190, y, "3");
	(f->n4) ? text_green(e, x + 210, y, "4") : text(e, x + 210, y, "4");
	(f->n5) ? text_green(e, x + 230, y, "5") : text(e, x + 230, y, "5");
	(f->n6) ? text_green(e, x + 250, y, "6") : text(e, x + 250, y, "6");
	(f->n7) ? text_green(e, x + 270, y, "7") : text(e, x + 270, y, "7");
	(f->n8) ? text_green(e, x + 290, y, "8") : text(e, x + 290, y, "8");
	(f->q) ? text_green(e, x + 430, y, "Q") : text(e, x + 430, y, "Q");
	(f->e) ? text_green(e, x + 450, y, "E") : text(e, x + 450, y, "E");
	show_menu2(e, x, y, e->flags);
}
