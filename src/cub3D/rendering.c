/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:09:27 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/23 15:09:29 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_minimap(t_cdata *data)
{
	int	xscale;
	int	yscale;

	xscale = (data->map_size.x * 10) / (data->map_size.x * (WIN_H / 451));
	yscale = (data->map_size.y * 10) / (data->map_size.y * (WIN_H / 451));
	image_to_fbuff(&data->mlx->frame_buffer, &data->minimap,
		(t_vec2){data->map_size.x * 10, data->map_size.y * 10}, (t_vec2){0, 0});
	circle_to_fbuff(data->mlx, (t_vec2){(data->p_pos.x * xscale),
		(data->p_pos.y * yscale)}, xscale * 0.25, (t_color){255, 255, 0, 0});
}

void	draw_background(t_cdata *data)
{
	float	j;
	int		i;

	i = -1;
	j = WIN_H / 2;
	square_to_fbuff(data->mlx,
		(t_rec){data->map_size.x * 1, 0, WIN_W, data->smallest_wall.x},
		data->map_col[0]);
	while (++i < WIN_H / 2)
	{
		if (i < data->smallest_wall.y)
			continue ;
		square_to_fbuff(data->mlx, (t_rec){0, WIN_H / 2 + i, WIN_W, 1},
			compute_floor_fog(data->map_col[0], data->map_col[1], j));
		j--;
	}
}

void	draw_wall_segment(t_cdata *data, int i, double depth, int dir)
{
	double	screen_dist;
	float	proj_height;
	float	texy;
	float	start;
	float	scale;

	//data->vert_tex_offset = (data->vert_tex_offset * TEX_RES) / TEX_RES;
	//data->hor_tex_offset = (data->hor_tex_offset * TEX_RES) / TEX_RES;
	screen_dist = ((WIN_W / 2) / tan(data->fov / 2));
	proj_height = screen_dist / (depth + 0.0001);
	start = ((WIN_H / 2) - (int)proj_height / 2);
	if (start < 0)
		start = 0;
	if (((WIN_H / 2) - (int)proj_height / 2) > data->smallest_wall.x
		|| proj_height < data->smallest_wall.y)
		data->smallest_wall = (t_vec2){(WIN_H / 2) - (int)proj_height / 2,
			proj_height};
	texy = 0;
	scale = TEX_RES / proj_height;
	if (proj_height >= WIN_H){
		texy = ((proj_height - WIN_H) / 2) * (TEX_RES / proj_height);
		proj_height = WIN_H;
	}
	for (float j = 0; j < proj_height && j + start < WIN_H; j++){
		square_to_fbuff(data->mlx, (t_rec){i * data->render_res,
			start + j, data->render_res,
			1}, select_basecolor(data, depth, dir, texy));
		texy += scale;
	}
}
