/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:56:52 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/10 14:56:54 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	pixel_to_fbuff(t_img *fbuff, t_vec2 pos, t_color col)
{
	char	*pixel;

	if (pos.x >= 0 && pos.y >= 0 && pos.x <= WIN_W && pos.y <= WIN_H)
	{
		pixel = fbuff->addr + (int)(pos.y * fbuff->line_length + pos.x
				* (fbuff->bpp / 8));
		*(int *)pixel = color_to_int(col);
	}
}

void	square_to_fbuff(t_img *fbuff, t_vec2 pos, t_vec2 size, t_color col)
{
	t_vec2	pos_buff;

	pos_buff = (t_vec2){pos.x - 1, pos.y - 1};
	while (++pos.x < (pos_buff.x + size.x))
	{
		while (++pos.y < (pos_buff.y + size.y))
			pixel_to_fbuff(fbuff, pos, col);
		pos.y = pos_buff.y;
	}
}

void	circle_to_fbuff(t_img *fbuff, t_vec2 pos, float radius, t_color col)
{
	t_count	c;
	t_vec2	pos_buff;

	c = (t_count){pos.x - radius - 1, pos.y - radius - 1, 0};
	pos_buff = (t_vec2){pos.x - radius, pos.y - radius};
	while (++c.i < (pos_buff.x + (radius * 2)))
	{
		while (++c.j < (pos_buff.y + (radius * 2)))
			if (vec2_dst((t_vec2){c.j, c.i}, pos) <= radius)
				pixel_to_fbuff(fbuff, (t_vec2){c.j, c.i}, col);
		c.j = pos_buff.y;
	}
}

void	image_to_fbuff(t_img *fbuff, t_img *img, t_vec2 size, t_vec2 pos)
{
	char	*pixel;
	int		i;

	i = -1;
	while (++i < (size.x * size.y) * (img->bpp / 8))
	{
		pixel = fbuff->addr + (int)(fbuff->line_length
				* ((i / img->line_length) + pos.y)
				+ ((i % img->line_length) + pos.x));
		*(int *)pixel = img->addr[i];
	}
}
