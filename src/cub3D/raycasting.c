/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:57:44 by aliaudet          #+#    #+#             */
/*   Updated: 2024/07/02 22:48:21 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_raydir_hor(t_vec3 ray_pos, double sin, t_cdata *data)
{
	int	dir;

	if (sin > 0)
	{
		dir = NORTH;
		data->hor_tex_offset = (data->img_size - 1)
			- (int)(ray_pos.x * data->img_size) % data->img_size;
	}
	if (ray_pos.y > (int)ray_pos.y)
	{
		dir = SOUTH;
		data->hor_tex_offset = (int)(ray_pos.x * data->img_size)
			% data->img_size;
	}
	return (dir);
}

double	get_hor_travel(t_cdata *data,
	t_vec2 cossin_a, t_vec3 values, int *raydir)
{
	t_vec3	ray_pos;
	int		i;

	i = -1;
	ray_pos.y = (int)data->p_pos.y - 0.000001;
	if (cossin_a.y > 0)
	{
		ray_pos.y = (int)data->p_pos.y + 1;
		values.y = 1;
	}
	ray_pos.z = (ray_pos.y - data->p_pos.y) / cossin_a.y;
	ray_pos.x = data->p_pos.x + ray_pos.z * cossin_a.x;
	values.z = values.y / cossin_a.y;
	values.x = values.z * cossin_a.x;
	while (++i < data->draw_distance)
	{
		if (check_ray_to_map_collision(data->map, data->map_size,
				(t_vec2){ray_pos.x, ray_pos.y}))
			return (*raydir = get_raydir_hor(ray_pos, cossin_a.y, data),
				ray_pos.z);
		ray_pos = (t_vec3){ray_pos.x + values.x, ray_pos.y + values.y,
			ray_pos.z + values.z};
	}
	return (ray_pos.z);
}

int	get_raydir_vert(t_vec3 ray_pos, double cos, t_cdata *data)
{
	int	dir;

	if (cos > 0)
	{
		dir = WEST;
		data->vert_tex_offset = (int)(ray_pos.y * data->img_size)
			% data->img_size;
	}
	if (ray_pos.x > (int)ray_pos.x)
	{
		dir = EAST;
		data->vert_tex_offset = (data->img_size - 1)
			- (int)(ray_pos.y * data->img_size) % data->img_size;
	}
	return (dir);
}

double	get_vert_travel(t_cdata *data,
	t_vec2 cossin_a, t_vec3 values, int *raydir)
{
	t_vec3	ray_pos;
	int		i;

	i = -1;
	ray_pos.x = (int)data->p_pos.x - 0.000001;
	if (cossin_a.x > 0)
	{
		ray_pos.x = (int)data->p_pos.x + 1;
		values.x = 1;
	}
	ray_pos.z = (ray_pos.x - data->p_pos.x) / cossin_a.x;
	ray_pos.y = data->p_pos.y + ray_pos.z * cossin_a.y;
	values.z = values.x / cossin_a.x;
	values.y = values.z * cossin_a.y;
	while (++i < data->draw_distance)
	{
		if (check_ray_to_map_collision(data->map, data->map_size,
				(t_vec2){ray_pos.x, ray_pos.y}))
			return (*raydir = get_raydir_vert(ray_pos, cossin_a.x, data),
				ray_pos.z);
		ray_pos = (t_vec3){ray_pos.x + values.x, ray_pos.y + values.y,
			ray_pos.z + values.z};
	}
	return (ray_pos.z);
}

void	raycasting(t_cdata *data)
{
	t_count	c;
	double	r_angle;
	t_vec2	cossin_a;
	t_vec2	delta_dist;

	c = (t_count){-1, EAST, SOUTH};
	r_angle = data->p_angle - (data->fov / 2) + 0.0001;
	data->ray_num = WIN_W / data->render_res;
	data->delta_angle = data->fov / data->ray_num;
	while (++c.i < data->ray_num)
	{
		cossin_a = (t_vec2){cos(r_angle), sin(r_angle)};
		delta_dist.x = get_vert_travel(data, cossin_a, (t_vec3){.x = -1}, &c.j);
		delta_dist.y = get_hor_travel(data, cossin_a, (t_vec3){.y = -1}, &c.k);
		if (delta_dist.x <= delta_dist.y)
			draw_wall_segment(data, c.i,
				delta_dist.x * cos(data->p_angle - r_angle), c.j);
		else
			draw_wall_segment(data, c.i,
				delta_dist.y * cos(data->p_angle - r_angle), c.k);
		r_angle += data->delta_angle;
	}
}
