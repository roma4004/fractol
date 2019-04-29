/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:48:59 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/21 21:50:47 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*text(t_env *restrict env, t_si_pt pt,
					char *restrict str, int is_active)
{
	if (!env || !str)
		return (NULL);
	mlx_string_put(env->mlx_ptr, env->win_ptr, pt.x, pt.y,
		(is_active) ? ACTIVE_MENU_COLOR : DEFAULT_MENU_COLOR, str);
	return (str);
}

void		show_values(t_env *restrict env, t_param p, int x, int y)
{
	x += (!env->flags.menu ? 550 : 0) + (!env->flags.hints ? 450 : 0);
	text(env, (t_si_pt){ x, y }, MSG_VAL_SEC, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_CUR_FRA, 0);
	text(env, (t_si_pt){ x + 170, y }, env->fract_names[p.fr_id], 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_ITER_LIM, 0);
	free(text(env, (t_si_pt){ x + 170, y }, ft_itoa(p.depth), 0));
	text(env, (t_si_pt){ x, y += 20 }, MSG_ITER_STE, 0);
	free(text(env, (t_si_pt){ x + 170, y }, ft_itoa(p.depth_step), 0));
	text(env, (t_si_pt){ x, y += 20 }, MSG_ZOOM, 0);
	free(text(env, (t_si_pt){ x + 170, y }, ft_itoa(p.display_zoom), 0));
	text(env, (t_si_pt){ x, y += 20 }, MSG_THREADS, 0);
	free(text(env, (t_si_pt){ x + 170, y }, ft_itoa(p.threads), 0));
	text(env, (t_si_pt){ x, y += 20 }, MSG_SHI_ALF, 0);
	free(text(env, (t_si_pt){ x + 170, y }, ft_itoa(p.color_shift.alpha), 0));
	text(env, (t_si_pt){ x, y += 20 }, MSG_SHI_RED, 0);
	free(text(env, (t_si_pt){ x + 170, y }, ft_itoa(p.color_shift.red), 0));
	text(env, (t_si_pt){ x, y += 20 }, MSG_SHI_GRE, 0);
	free(text(env, (t_si_pt){ x + 170, y }, ft_itoa(p.color_shift.green), 0));
	text(env, (t_si_pt){ x, y += 20 }, MSG_SHI_BLU, 0);
	free(text(env, (t_si_pt){ x + 170, y }, ft_itoa(p.color_shift.blue), 0));
}

void		show_combo(t_env *restrict env, bool menu, int x, int y)
{
	x += ((!menu) ? 550 : 0);
	text(env, (t_si_pt){ x, y }, MSG_HINTS, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_BG, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_WIND, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_LEAF, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_FLOWER, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_CLOUDS, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_BLADES, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_SHIP, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_TRICORN, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_LOHNES, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_HEART, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_MIR_HOR, 0);
	text(env, (t_si_pt){ x, y + 20 }, MSG_MIR_VER, 0);
}

static void	show_menu2(t_env *restrict e, t_flags f, int x, int y)
{
	text(e, (t_si_pt){ x, y += 20 }, MSG_CARIOID, 0);
	text(e, (t_si_pt){ x + 150, y }, MSG_CARIOID_Y, f.carioid);
	text(e, (t_si_pt){ x, y += 20 }, MSG_CARIOID_COL, 0);
	text(e, (t_si_pt){ x + 150, y }, MSG_CARIOID_W, f.w);
	text(e, (t_si_pt){ x, y += 20 }, MSG_STYLE, 0);
	text(e, (t_si_pt){ x + 150, y }, MSG_STYLE_T, f.range);
	text(e, (t_si_pt){ x + 180, y }, MSG_STYLE_G, f.alt_col);
	text(e, (t_si_pt){ x, y += 20 }, MSG_MOUSE_DET, 0);
	text(e, (t_si_pt){ x + 210, y }, MSG_MOUSE_DET_R, f.lock_julia);
	text(e, (t_si_pt){ x, y += 20 }, MSG_THREAD_NUM, 0);
	text(e, (t_si_pt){ x, y += 20 }, MSG_SHIFT_ARGB, 0);
	text(e, (t_si_pt){ x, y += 20 }, MSG_RADIUS, 0);
	text(e, (t_si_pt){ x, y += 20 }, MSG_TRIM, 0);
	text(e, (t_si_pt){ x, y += 20 }, MSG_CURVE_X, 0);
	text(e, (t_si_pt){ x, y += 20 }, MSG_CURVE_Y, 0);
	text(e, (t_si_pt){ x, y += 20 }, MSG_MENU_SW, 0);
	text(e, (t_si_pt){ x, y += 20 }, MSG_COMBO_SW, 0);
	text(e, (t_si_pt){ x, y + 20 }, MSG_VALUE_SW, 0);
}

void		show_menu(t_env *restrict env, t_flags flags, int x, int y)
{
	text(env, (t_si_pt){ x, y }, MSG_MENU_SEC, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_ZOOM_M, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_NEXT_FRA, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_DEPTH, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_DEPTH_STEP, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_RESET, 0);
	text(env, (t_si_pt){ x, y += 20 }, MSG_EFFECTS, 0);
	text(env, (t_si_pt){ x + 150, y }, MSG_EFFECTS_1, flags.n1);
	text(env, (t_si_pt){ x + 170, y }, MSG_EFFECTS_2, flags.n2);
	text(env, (t_si_pt){ x + 190, y }, MSG_EFFECTS_3, flags.n3);
	text(env, (t_si_pt){ x + 210, y }, MSG_EFFECTS_4, flags.n4);
	text(env, (t_si_pt){ x + 230, y }, MSG_EFFECTS_5, flags.n5);
	text(env, (t_si_pt){ x + 250, y }, MSG_EFFECTS_6, flags.n6);
	text(env, (t_si_pt){ x + 270, y }, MSG_EFFECTS_7, flags.n7);
	text(env, (t_si_pt){ x + 290, y }, MSG_EFFECTS_8, flags.n8);
	text(env, (t_si_pt){ x + 310, y }, MSG_EFFECTS_9, flags.n9);
	text(env, (t_si_pt){ x + 450, y }, MSG_EFFECTS_Q, flags.q);
	text(env, (t_si_pt){ x + 470, y }, MSG_EFFECTS_E, flags.e);
	show_menu2(env, flags, x, y);
}
