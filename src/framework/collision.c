/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:44:17 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/13 11:44:18 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub_framework.h>

int	check_collision_point_rec(t_rec rec, t_vec2 point)
{
	if ((point.x >= rec.x && point.x < (rec.x + rec.width))
		&& (point.y >= rec.y && point.y < (rec.y + rec.height)))
		return (1);
	return (0);
}
