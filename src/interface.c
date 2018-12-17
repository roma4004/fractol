/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:48:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/12/13 18:59:35 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*text(t_env *env, t_int_pt pt, char *str, int is_active)
{
	if (env && str)
	{
		mlx_string_put(env->mlx_ptr, env->win_ptr, pt.x, pt.y,
			(is_active) ? ACTIVE_MENU_COLOR : DEFAULT_MENU_COLOR, str);
		return (str);
	}
	return (NULL);
}

void		show_values(t_env *env, t_param *param, int x, int y)
{
	x += ((!env->flags->menu) ? 550 : 0)
		+ ((!env->flags->hints) ? 450 : 0);
	text(env, (t_int_pt){x, y}, "ACTUAL VALUES  :", 0);
	text(env, (t_int_pt){x, y += 20}, "current fractal: ", 0);
	text(env, (t_int_pt){x + 170, y}, env->names[env->param->fr_id], 0);
	text(env, (t_int_pt){x, y += 20}, "iteration limit:", 0);
	free(text(env, (t_int_pt){x + 170, y}, ft_itoa(param->depth), 0));
	text(env, (t_int_pt){x, y += 20}, "iteration step :", 0);
	free(text(env, (t_int_pt){x + 170, y}, ft_itoa(param->depth_step), 0));
	text(env, (t_int_pt){x, y += 20}, "zoom           :", 0);
	free(text(env, (t_int_pt){x + 170, y}, ft_itoa(param->display_zoom), 0));
	text(env, (t_int_pt){x, y += 20}, "threads        :", 0);
	free(text(env, (t_int_pt){x + 170, y}, ft_itoa(param->threads), 0));
	text(env, (t_int_pt){x, y += 20}, "shift alpha    :", 0);
	free(text(env, (t_int_pt){x + 170, y}, ft_itoa(param->col_shift.alpha), 0));
	text(env, (t_int_pt){x, y += 20}, "shift red      :", 0);
	free(text(env, (t_int_pt){x + 170, y}, ft_itoa(param->col_shift.red), 0));
	text(env, (t_int_pt){x, y += 20}, "shift green    :", 0);
	free(text(env, (t_int_pt){x + 170, y}, ft_itoa(param->col_shift.green), 0));
	text(env, (t_int_pt){x, y += 20}, "shift blue     :", 0);
	free(text(env, (t_int_pt){x + 170, y}, ft_itoa(param->col_shift.blue), 0));
}

void		show_combo(t_env *env, int x, int y)
{
	x += ((!env->flags->menu) ? 550 : 0);
	text(env, (t_int_pt){x, y}, "COMBO HINT:", 0);
	text(env, (t_int_pt){x, y += 20}, "background: r + q + e", 0);
	text(env, (t_int_pt){x, y += 20}, "wind      : r + q, r + e", 0);
	text(env, (t_int_pt){x, y += 20}, "leaf      : r + 4 or num_4", 0);
	text(env, (t_int_pt){x, y += 20}, "flower    : r + 8 or num_8", 0);
	text(env, (t_int_pt){x, y += 20},
								"clouds    : r + 4 or num_4 + 8 or num_8", 0);
	text(env, (t_int_pt){x, y += 20},
								"blades    : r + 4 + Z (press Z 17 times)", 0);
	text(env, (t_int_pt){x, y += 20},
								"burn ship : r + 2 + 3 (for Mandelbrot)", 0);
	text(env, (t_int_pt){x, y += 20}, "tricorn   : r + 2 (for Mandelbrot)", 0);
	text(env, (t_int_pt){x, y += 20}, "lohnes    : r + q, e, t)", 0);
	text(env, (t_int_pt){x, y += 20}, "heart     : r + 3 or num_3", 0);
	text(env, (t_int_pt){x, y += 20}, "mirror hor: 6 or num_6", 0);
	text(env, (t_int_pt){x, y + 20},
								"mirror ver: 7 or num_7 (for Ship, Lohnes)", 0);
}

static void show_menu2(t_env *e, t_flags *f, int x, int y)
{
	text(e, (t_int_pt){x, y += 20}, "calc carioid :", 0);
	text(e, (t_int_pt){x + 150, y}, "Y", f->carioid);
	text(e, (t_int_pt){x, y += 20},
							"white carioid:   (when calc carioid is on)", 0);
	text(e, (t_int_pt){x + 150, y}, "W", f->w);
	text(e, (t_int_pt){x, y += 20}, "color style  :  ,   ", 0);
	text(e, (t_int_pt){x + 150, y}, "T", f->range);
	text(e, (t_int_pt){x + 180, y}, "G", f->alt_color);
	text(e, (t_int_pt){x, y += 20}, "mouse detect : mouse_", 0);
	text(e, (t_int_pt){x + 210, y}, "R", f->lock_julia);
	text(e, (t_int_pt){x, y += 20}, "threads num  : (+, -) U, J", 0);
	text(e, (t_int_pt){x, y += 20},
						"shift ARGB   : (+, -) A, Z,  S, X,  D, C,  F, V", 0);
	text(e, (t_int_pt){x, y += 20}, "radius change: Home, End", 0);
	text(e, (t_int_pt){x, y += 20},
						"trim change  : Page_Up, Page_Down (for 5 effect)", 0);
	text(e, (t_int_pt){x, y += 20},
						"curve X      : Home, End (for Barnsley)", 0);
	text(e, (t_int_pt){x, y += 20},
						"curve Y      : Page_Up, Page_Down (for Fern)", 0);
	text(e, (t_int_pt){x, y += 20}, "menu         : M", 0);
	text(e, (t_int_pt){x, y += 20}, "combo        : H", 0);
	text(e, (t_int_pt){x, y + 20}, "values       : N", 0);
}

void show_menu(t_env *env, t_flags *flags, int x, int y)
{
	text(env, (t_int_pt){x, y}, "MENU         :", 0);
	text(env, (t_int_pt){x, y += 20}, "zoom         : -, + or mouse scroll", 0);
	text(env, (t_int_pt){x, y += 20}, "next fractal : Enter", 0);
	text(env, (t_int_pt){x, y += 20}, "depth        : num_+, num_- or 9, 0", 0);
	text(env, (t_int_pt){x, y += 20}, "depth step   : num_/, num_*", 0);
	text(env, (t_int_pt){x, y += 20}, "reset        : R", 0);
	text(env, (t_int_pt){x, y += 20},
							"effects      :                 (or numpad)", 0);
	text(env, (t_int_pt){x + 150, y}, "1", flags->n1);
	text(env, (t_int_pt){x + 170, y}, "2", flags->n2);
	text(env, (t_int_pt){x + 190, y}, "3", flags->n3);
	text(env, (t_int_pt){x + 210, y}, "4", flags->n4);
	text(env, (t_int_pt){x + 230, y}, "5", flags->n5);
	text(env, (t_int_pt){x + 250, y}, "6", flags->n6);
	text(env, (t_int_pt){x + 270, y}, "7", flags->n7);
	text(env, (t_int_pt){x + 290, y}, "8", flags->n8);
	text(env, (t_int_pt){x + 430, y}, "Q", flags->q);
	text(env, (t_int_pt){x + 450, y}, "E", flags->e);
	show_menu2(env, env->flags, x, y);
}
