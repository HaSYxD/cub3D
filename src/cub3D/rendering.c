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
	image_to_fbuff(&data->mlx->frame_buffer, &data->minimap,
		(t_vec2){data->map_size.x * 10, data->map_size.y * 10}, (t_vec2){0, 0});
	circle_to_fbuff(data->mlx, (t_vec2){(data->p_pos.x * data->minim_scale.x),
		(data->p_pos.y * data->minim_scale.y)}, data->minim_scale.x * 0.25,
		(t_color){255, 255, 0, 0});
}

void	draw_background(t_cdata *data)
{
	float	j;
	int		i;

	i = -1;
	j = WIN_H / 2;
	square_to_fbuff(data->mlx,
		(t_rec){data->map_size.x * data->minim_scale.x, 0,
		WIN_W - (data->map_size.x * data->minim_scale.x),
		data->map_size.y * data->minim_scale.y}, data->map_col[0]);
	square_to_fbuff(data->mlx,
		(t_rec){0, data->map_size.y * data->minim_scale.y, WIN_W,
		data->smallest_wall.x - (data->map_size.y * data->minim_scale.y)},
		data->map_col[0]);
	while (++i < WIN_H / 2)
	{
		if (i < data->smallest_wall.y)
			continue ;
		square_to_fbuff(data->mlx, (t_rec){0, WIN_H / 2 + i, WIN_W, 1},
			compute_floor_fog(data->fog_col, data->map_col[1], j));
		j--;
	}
}

void	get_smallest_wall(t_cdata *data, float proj_height, t_vec3 val)
{
	if (val.y > data->smallest_wall.x || proj_height < data->smallest_wall.y)
		data->smallest_wall = (t_vec2){(WIN_H / 2) - (int)proj_height / 2,
			proj_height};
}

//val.x == Y texture offset
//val.y == Y Wall offset
//val.z == Drawing scale
void	draw_wall_segment(t_cdata *data, int i, double depth, int dir)
{
	double	screen_dist;
	t_vec3	val;
	float	j;
	float	proj_height;

	j = -1;
	screen_dist = ((WIN_W / 2) / tan(data->fov / 2));
	proj_height = screen_dist / (depth + 0.0001);
	val = (t_vec3){0, ((WIN_H / 2) - (int)proj_height / 2),
		data->img_size / proj_height};
	if (val.y < 0)
		val.y = 0;
	if (proj_height >= WIN_H)
	{
		val.x = ((proj_height - WIN_H) / 2) * (data->img_size / proj_height);
		proj_height = WIN_H;
	}
	get_smallest_wall(data, proj_height, val);
	while (++j < proj_height && (j + val.y) < WIN_H)
	{
		square_to_fbuff(data->mlx, (t_rec){i * data->render_res,
			val.y + j, data->render_res,
			1}, select_basecolor(data, depth, dir, val.x));
		val.x += val.z;
	}
}
