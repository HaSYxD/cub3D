/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:18:14 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/10 22:18:15 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	color_to_int(t_color col)
{
	return (col.a << 24 | col.r << 16 | col.g << 8 | col.b);
}

t_color	int_to_color(int col)
{
	t_color	c;
	int		i;

	i = -1;
	while (++i < 8)
		c.r = col << i;
	while (++i < 16)
		c.g = col << i;
	while (++i < 24)
		c.b = col << i;
	while (++i < 32)
		c.a = col << i;
	return (c);
}
