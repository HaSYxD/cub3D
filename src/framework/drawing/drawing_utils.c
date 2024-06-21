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

#include <cub_framework.h>

int	color_to_int(t_color col)
{
	return (col.a << 24 | col.r << 16 | col.g << 8 | col.b);
}

t_color	int_to_color(int col)
{
	return ((t_color){
		(col & 0xFF000000) >> 24,
		(col & 0x00FF0000) >> 16,
		(col & 0x0000FF00) >> 8,
		col & 0x000000FF});
}
