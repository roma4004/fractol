/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ram_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:23:50 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/03 13:58:58 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		free_win(t_win *win)
{
	if (win)
	{
		if (win->param)
			ft_memdel((void *)&win->param);
		ft_memdel((void *)&win->flags);
		ft_memdel((void *)&win);
		return (1);
	}
	return (0);
}
