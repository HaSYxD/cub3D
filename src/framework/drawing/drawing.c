/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:56:52 by aliaudet          #+#    #+#             */
/*   Updated: 2024/07/05 11:02:25 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub_framework.h>

void	pixel_to_fbuff(t_mlxctx *mlx, t_vec2 pos, t_color col)
{
	char	*pixel;

	if (pos.x < 0 || pos.y < 0 || pos.x > mlx->win_w || pos.y > mlx->win_h)
		return ;
	pixel = mlx->frame_buffer.addr + (int)(pos.y
			* mlx->frame_buffer.line_length + pos.x
			* (mlx->frame_buffer.bpp * 0.125));
	*(int *)pixel = color_to_int(col);
}

void	square_to_fbuff(t_mlxctx *mlx, t_rec rec, t_color col)
{
	t_vec2	pos_buff;
	int		x_max;
	int		y_max;

	x_max = rec.x + rec.width;
	y_max = rec.y + rec.height;
	pos_buff = (t_vec2){rec.x - 1, rec.y - 1};
	while (++pos_buff.y < y_max)
	{
		while (++pos_buff.x < x_max)
			pixel_to_fbuff(mlx, pos_buff, col);
		pos_buff.x = rec.x - 1;
	}
}

void	circle_to_fbuff(t_mlxctx *mlx, t_vec2 pos, float radius, t_color col)
{
	t_vec2	pos_buff;

	pos_buff = (t_vec2){pos.x - radius - 1, pos.y - radius - 1};
	while (++pos_buff.y < (pos.y + (radius * 2)))
	{
		while (++pos_buff.x < (pos.x + (radius * 2)))
			if (vec2_dst((t_vec2){pos_buff.x, pos_buff.y}, pos) <= radius)
				pixel_to_fbuff(mlx, (t_vec2){(int)pos_buff.x,
					(int)pos_buff.y}, col);
		pos_buff.x = pos.x - radius - 1;
	}
}

void	image_to_fbuff(t_img *fbuff, t_img *img, t_vec2 size, t_vec2 pos)
{
	char	*pixel;
	int		i;
	int		limit;

	i = -1;
	limit = (size.x * size.y) * (img->bpp / 8);
	while (++i < limit)
	{
		if (!img->addr[i] && i > 0 && !img->addr[i - 1])
			continue ;
		pixel = fbuff->addr + (int)(fbuff->line_length
				* ((i / img->line_length) + pos.y)
				+ ((i % img->line_length) + pos.x));
		*(int *)pixel = img->addr[i];
	}
}
