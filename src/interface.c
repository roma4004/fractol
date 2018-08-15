/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 14:48:59 by dromanic          #+#    #+#             */
/*   Updated: 2018/07/24 14:49:03 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	show_interface(t_win *win)
{
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 10, DEF_COLOR,
		"move            : arrows left, up, down, right");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 30, DEF_COLOR,
		"zoom all        : -, + or mouse scroll");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 50, DEF_COLOR,
		"zoom only Z     : 9, 0 or numpad +, -");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 70, DEF_COLOR,
		"interface       : 8 or numpad 8");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 90, DEF_COLOR,
		"rotate X,Y,Z(+-): QA, WS, ED");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 130, DEF_COLOR,
		"reset           : R");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 150, DEF_COLOR,
		"add visual style: 1..7 or numpad 1..7 (|, /, -, \\, fdf, layer, dot)");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 110, DEF_COLOR,
		"next style      : enter (hold to animate)");
}
