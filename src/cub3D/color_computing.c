/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_computing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:29:44 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/24 15:29:45 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_color	compute_wall_fog(t_color fog_col, t_color wall_col,
	double dst, uint8_t draw_dst)
{
	float	fog_percent;

	fog_percent = 1.0f * (dst / draw_dst);
	return ((t_color){254,
		(1.0f - fog_percent) * wall_col.r + (fog_percent * fog_col.r),
		(1.0f - fog_percent) * wall_col.g + (fog_percent * fog_col.g),
		(1.0f - fog_percent) * wall_col.b + (fog_percent * fog_col.b)});
}

t_color	compute_floor_fog(t_color fog_col, t_color floor_col, float depth)
{
	float	fog_percent;

	fog_percent = 1.0f * (depth / WIN_H);
	return ((t_color){254,
		(1.0f - fog_percent) * floor_col.r + fog_percent * fog_col.r,
		(1.0f - fog_percent) * floor_col.g + fog_percent * fog_col.g,
		(1.0f - fog_percent) * floor_col.b + fog_percent * fog_col.b});
}

t_color	get_texture_color(t_cdata *data, int i, int x, int y)
{
	char	*pixel;
	t_img	*img;

	img = &data->wall_tex_img[i];
	pixel = img->addr + (int)(img->line_length * y + x * (img->bpp / 8));
	return (int_to_color(*(int *)pixel));
}

t_color	color_reduction(t_color c, uint8_t value)
{
	if (value == 0)
		return (c);
	return ((t_color){.a = c.a,
		.r = c.r - (c.r / value),
		.g = c.g - (c.g / value),
		.b = c.b - (c.b / value),
	});
}

t_color	select_basecolor(t_cdata *data, double depth, int dir, int y)
{
	t_color	c;

	if (dir == NORTH)
		c = color_reduction(get_texture_color(data, 0,
					data->hor_tex_offset, y), data->hor_shading);
	else if (dir == EAST)
		c = color_reduction(get_texture_color(data, 3,
					data->vert_tex_offset, y), data->vert_shading);
	else if (dir == SOUTH)
		c = color_reduction(get_texture_color(data, 2,
					data->hor_tex_offset, y), data->hor_shading);
	else if (dir == WEST)
		c = color_reduction(get_texture_color(data, 1,
					data->vert_tex_offset, y), data->vert_shading);
	else
		c = (t_color){254, 0, 0, 0};
	return (compute_wall_fog(data->fog_col, c,
			depth, data->draw_distance));
}
