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

t_color	compute_wall_fog(t_color fog_col, t_color wall_col,
	double dst, uint8_t draw_dst)
{
	float	fog_percent;

	fog_percent = 1.0f * (dst / draw_dst);
	return ((t_color){255,
		(1.0f - fog_percent) * wall_col.r + fog_percent * fog_col.r,
		(1.0f - fog_percent) * wall_col.g + fog_percent * fog_col.g,
		(1.0f - fog_percent) * wall_col.b + fog_percent * fog_col.b});
}

t_color	compute_floor_fog(t_color fog_col, t_color floor_col, float depth)
{
	float	fog_percent;

	fog_percent = 1.0f * (depth / WIN_H);
	return ((t_color){255,
		(1.0f - fog_percent) * floor_col.r + fog_percent * fog_col.r,
		(1.0f - fog_percent) * floor_col.g + fog_percent * fog_col.g,
		(1.0f - fog_percent) * floor_col.b + fog_percent * fog_col.b});
}

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

void	draw_wall_segment(t_cdata *data, int i, double depth, t_color base_col)
{
	double	screen_dist;
	float	proj_height;

	screen_dist = (WIN_W / 2) / tan(data->fov / 2);
	proj_height = screen_dist / (depth + 0.0001);
	if (proj_height > WIN_H)
		proj_height = WIN_H;
	if (((WIN_H / 2) - (int)proj_height / 2) > data->smallest_wall.x
		|| proj_height < data->smallest_wall.y)
		data->smallest_wall = (t_vec2){(WIN_H / 2) - (int)proj_height / 2,
			proj_height};
	base_col = compute_wall_fog(data->map_col[0],
			base_col, depth, data->draw_distance);
	square_to_fbuff(data->mlx, (t_rec){i * data->render_res,
		(WIN_H / 2) - (int)proj_height / 2, data->render_res,
		proj_height}, base_col);
}
