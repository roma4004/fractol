/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:48:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/18 18:56:35 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		show_values(t_env *env, int x, int y)
{
	x += ((!env->flags->menu_off) ? 550 : 0)
		+ ((!env->flags->hints_off) ? 450 : 0);
	text(env, x, y, "ACTUAL VALUES  :");
	text(env, x, y += 20, "current fractal: ");
	(env->param->fr_id == 0) && (text(env, x + 170, y, "Barnsley"));
	(env->param->fr_id == 1) && (text(env, x + 170, y, "Mandelbrot"));
	(env->param->fr_id == 2) && (text(env, x + 170, y, "Batman"));
	(env->param->fr_id == 3) && (text(env, x + 170, y, "Mandelbrot cuboid"));
	(env->param->fr_id == 4) && (text(env, x + 170, y, "Julia"));
	text(env, x, y += 20, "iteration limit:");
	free(text(env, x + 170, y, ft_itoa(env->param->fr_depth)));
	text(env, x, y += 20, "iteration step :");
	free(text(env, x + 170, y, ft_itoa(env->param->fr_depth_step)));
	text(env, x, y += 20, "zoom           :");
	free(text(env, x + 170, y, ft_itoa(env->param->display_zoom)));
	text(env, x, y += 20, "threads        :");
	free(text(env, x + 170, y, ft_itoa(env->param->threads)));
	text(env, x, y += 20, "shift alpha    :");
	free(text(env, x + 170, y, ft_itoa(env->param->alpha_shift)));
	text(env, x, y += 20, "shift red      :");
	free(text(env, x + 170, y, ft_itoa(env->param->red_shift)));
	text(env, x, y += 20, "shift green    :");
	free(text(env, x + 170, y, ft_itoa(env->param->green_shift)));
	text(env, x, y += 20, "shift blue     :");
	free(text(env, x + 170, y, ft_itoa(env->param->blue_shift)));
}

void		show_combo(t_env *env, int x, int y)
{
	x += ((!env->flags->menu_off) ? 550 : 0);
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
	text(env, x, y + 20, "mirror ver: 7 or num_7 (for Ship, Lohnes)");
}

static void	show_menu2(t_env *env, int x, int y, t_flags *f)
{
	text(env, x, y += 20, "calc carioid :");
	(f->if_carioid) ? text_green(env, x + 150, y, "Y")
					: text(env, x + 150, y, "Y");
	text(env, x, y += 20, "white carioid:   (when calc carioid is on)");
	(f->w) ? text_green(env, x + 150, y, "W") : text(env, x + 150, y, "W");
	text(env, x, y += 20, "color style  :  ,   ");
	(f->col_range) ? text_green(env, x + 150, y, "T")
					: text(env, x + 150, y, "T");
	(f->alt_color) ? text_green(env, x + 180, y, "G")
					: text(env, x + 180, y, "G");
	text(env, x, y += 20, "mouse detect : mouse_");
	(f->lock_julia) ? text_green(env, x + 210, y, "R")
					: text(env, x + 210, y, "R");
	text(env, x, y += 20, "threads num  : (+, -) U, J");
	text(env, x, y += 20, "shift ARGB   : (+, -) A, Z,  S, X,  D, C,  F, V");
	text(env, x, y += 20, "radius change: Home, End");
	text(env, x, y += 20, "trim change  : Page_Up, Page_Down (for 5 effect)");
	text(env, x, y += 20, "curve X      : Home, End (for Barnsley)");
	text(env, x, y += 20, "curve Y      : Page_Up, Page_Down (for Barnsley)");
	text(env, x, y += 20, "menu         : M");
	text(env, x, y += 20, "combo        : H");
	text(env, x, y + 20, "values       : N");
}

void		show_menu(t_env *env, int x, int y, t_flags *flags)
{
	text(env, x, y, "MENU         :");
	text(env, x, y += 20, "zoom         : -, + or mouse scroll");
	text(env, x, y += 20, "next fractal : Enter");
	text(env, x, y += 20, "depth        : num_+, num_- or 9, 0");
	text(env, x, y += 20, "depth step   : num_/, num_*");
	text(env, x, y += 20, "reset        : R");
	text(env, x, y += 20, "effects      :                 (or numpad)");
	(flags->n1) ? text_green(env, x + 150, y, "1") : text(env, x + 150, y, "1");
	(flags->n2) ? text_green(env, x + 170, y, "2") : text(env, x + 170, y, "2");
	(flags->n3) ? text_green(env, x + 190, y, "3") : text(env, x + 190, y, "3");
	(flags->n4) ? text_green(env, x + 210, y, "4") : text(env, x + 210, y, "4");
	(flags->n5) ? text_green(env, x + 230, y, "5") : text(env, x + 230, y, "5");
	(flags->n6) ? text_green(env, x + 250, y, "6") : text(env, x + 250, y, "6");
	(flags->n7) ? text_green(env, x + 270, y, "7") : text(env, x + 270, y, "7");
	(flags->n8) ? text_green(env, x + 290, y, "8") : text(env, x + 290, y, "8");
	(flags->q) ? text_green(env, x + 430, y, "Q") : text(env, x + 430, y, "Q");
	(flags->e) ? text_green(env, x + 450, y, "E") : text(env, x + 450, y, "E");
	show_menu2(env, x, y, env->flags);
}
