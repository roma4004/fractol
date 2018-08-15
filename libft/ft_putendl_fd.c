/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:50:41 by dromanic          #+#    #+#             */
/*   Updated: 2017/11/19 19:54:39 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl_fd(char const *s, int fd)
{
	unsigned int i;

	if (!s)
		return ;
	i = 0;
	while (s && s[i])
		i++;
	write(fd, s, i);
	write(fd, "\n", 1);
}
