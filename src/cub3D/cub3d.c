/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:03:30 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/20 14:02:06 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	res = 10;

double	get_hor_travel(t_cdata *data, t_vec2 cossin_a)
{
	t_vec3	values;
	t_vec3	ray_pos;
	int		i;

	i = -1;
	ray_pos.y = (int)data->p_pos.y - 0.000001;
	values.y = -1;
	if (cossin_a.y > 0)
	{
		ray_pos.y = (int)data->p_pos.y + 1;
		values.y = 1;
	}
	ray_pos.z = (ray_pos.y - data->p_pos.y) / cossin_a.y;
	ray_pos.x = data->p_pos.x + ray_pos.z * cossin_a.x;
	values.z = values.y / cossin_a.y;
	values.x = values.z * cossin_a.x;
	while (++i < DRAW_DISTANCE)
	{
		if (check_player_to_map_collision(data->map, data->map_size,
				(t_vec2){ray_pos.x, ray_pos.y}))
			break ;
		ray_pos = (t_vec3){ray_pos.x + values.x, ray_pos.y + values.y,
			ray_pos.z + values.z};
	}
	return (ray_pos.z);
}

double	get_vert_travel(t_cdata *data, t_vec2 cossin_a)
{
	t_vec3	ray_pos;
	t_vec3	values;
	int		i;

	i = -1;
	ray_pos.x = (int)data->p_pos.x - 0.000001;
	values.x = -1;
	if (cossin_a.x > 0)
	{
		ray_pos.x = (int)data->p_pos.x + 1;
		values.x = 1;
	}
	ray_pos.z = (ray_pos.x - data->p_pos.x) / cossin_a.x;
	ray_pos.y = data->p_pos.y + ray_pos.z * cossin_a.y;
	values.z = values.x / cossin_a.x;
	values.y = values.z * cossin_a.y;
	while (++i < DRAW_DISTANCE)
	{
		if (check_player_to_map_collision(data->map, data->map_size,
				(t_vec2){ray_pos.x, ray_pos.y}))
			break ;
		ray_pos = (t_vec3){ray_pos.x + values.x, ray_pos.y + values.y,
			ray_pos.z + values.z};
	}
	return (ray_pos.z);
}

void	raycasting(t_cdata *data)
{
	int	r_num = WIN_W/res;
	double	dangle = FOV / r_num;
	double	r_angle = data->p_angle - (FOV/2) + 0.0001;
	t_vec2	delta_dist;

	for (int i = 0; i < r_num; i++){
		delta_dist = (t_vec2){get_vert_travel(data, (t_vec2){cos(r_angle), sin(r_angle)}),
				get_hor_travel(data, (t_vec2){cos(r_angle), sin(r_angle)})};
		t_color	c;
		double	depth;
		float	fog_percent;

		depth = delta_dist.y;
		fog_percent = 1.0f * (depth / DRAW_DISTANCE);
		c = (t_color){255, (1.0f - fog_percent) * 150 + fog_percent * data->map_col[0].r,
			 (1.0f - fog_percent) * 150 + fog_percent * data->map_col[0].g,
			 (1.0f - fog_percent) * 150 + fog_percent * data->map_col[0].b};
		if (delta_dist.x < delta_dist.y)
		{
			depth = delta_dist.x;
			fog_percent = 1.0f * (depth / DRAW_DISTANCE);
			c = (t_color){255, (1.0f - fog_percent) * 255 + fog_percent * data->map_col[0].r,
				 (1.0f - fog_percent) * 255 + fog_percent * data->map_col[0].g,
				 (1.0f - fog_percent) * 255 + fog_percent * data->map_col[0].b};
		}
		depth *= cos(data->p_angle - r_angle);
		double screen_dist = (WIN_W/2) / tan(FOV/2);
		float	proj_height = screen_dist / (depth + 0.0001);
		if (proj_height > WIN_H)
			proj_height = WIN_H;
		square_to_fbuff(data->mlx, (t_rec){i*res, (WIN_H/2) - (int)proj_height / 2, res, proj_height}, c);
		r_angle += dangle;
	}
}

void	draw_minimap(t_cdata *data)
{
	int	xscale;
	int	yscale;

	xscale = (WIN_W/6) / (data->map_size.x * (WIN_H / 451));
	yscale = (WIN_H/6) / (data->map_size.y * (WIN_H / 451));
	image_to_fbuff(&data->mlx->frame_buffer, &data->minimap, (t_vec2){WIN_W/6, WIN_H/6}, (t_vec2){0, 0});
	circle_to_fbuff(data->mlx, (t_vec2){(data->p_pos.x*xscale),
		(data->p_pos.y*yscale)}, xscale*0.25, (t_color){255, 255, 0, 0});
}

int	exit_cub3d(t_cdata *data)
{
	destroy_mlxctx(data->mlx);
	exit(0);
}

static int	render(t_cdata *data)
{
	if (is_key_down(data->mlx, XK_Escape))
		exit_cub3d(data);
	if (is_key_down(data->mlx, XK_Up)){
		res--;
		if (res < 1)
			res = 1;
		data->mlx->key_state[0] = 0;
	}
	else if (is_key_down(data->mlx, XK_Down)){
		res++;
		if (res > 20)
			res = 20;
		data->mlx->key_state[0] = 0;
	}
	player_move(data);
	square_to_fbuff(data->mlx, (t_rec){0, 0, WIN_W, WIN_H/2}, data->map_col[0]);
	float	fog_percent;
	float	j = WIN_H/2;
	for (float i = 0; i < WIN_H/2; i++){
		fog_percent = 1.0f * (j / WIN_H);
		square_to_fbuff(data->mlx, (t_rec){0, WIN_H/2 + i, WIN_W, 1}, (t_color){255, (1.0f - fog_percent) * data->map_col[1].r + fog_percent * data->map_col[0].r,
											(1.0f - fog_percent) * data->map_col[1].g + fog_percent * data->map_col[0].g,
											(1.0f - fog_percent) * data->map_col[1].b + fog_percent * data->map_col[0].b});
		j--;
	}
	j = WIN_H/2;
	raycasting(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->frame_buffer.img, 0, 0);
	print_fps_to_consol(data->mlx);
	return (0);
}

void	compute_minimap(t_cdata *data)
{
	t_count	c;
	int	xscale;
	int	yscale;

	c = (t_count){-1, -1, 0};
	xscale = (WIN_W/6) / (data->map_size.x * (WIN_H / 451));
	yscale = (WIN_H/6) / (data->map_size.y * (WIN_H / 451));
	data->minimap.img = mlx_new_image(data->mlx->mlx, WIN_W/6, WIN_H/6);
	data->minimap.addr = mlx_get_data_addr(data->minimap.img,
		&data->minimap.bpp, &data->minimap.line_length,
		&data->minimap.endian);
	square_to_fbuff(data->mlx, (t_rec){0, 0, xscale*data->map_size.x, yscale*data->map_size.y}, (t_color){255, 0, 0, 30});
	while (++c.i < data->map_size.y)
	{
		while (++c.j < data->map_size.x)
		{
			if (data->map[c.i][c.j] == '1')
				square_to_fbuff(data->mlx, (t_rec){c.j * xscale, c.i * yscale,
					xscale - 1, yscale - 1}, (t_color){255, 0, 0, 255});
			else if (data->map[c.i][c.j] == '0')
				square_to_fbuff(data->mlx, (t_rec){c.j * xscale, c.i * yscale,
					xscale - 1, yscale - 1}, (t_color){255, 0, 0, 55});
		}
		c.j = -1;
	}
	image_to_fbuff(&data->minimap, &data->mlx->frame_buffer, (t_vec2){WIN_W/6, WIN_H}, (t_vec2){0, 0});
}

void	run_cub3d(t_cdata *data)
{
	for (int i = 0; i < data->map_size.x; i++)
		for (int j = 0; j < data->map_size.y; j++)
			if (data->map[j][i] == 'N')
				data->p_pos = (t_vec2){i, j};
	data->p_angle = -(M_PI/2);
	compute_minimap(data);
	mlx_hook(data->mlx->win, KeyPress, KeyPressMask, key_press, data->mlx);
	mlx_hook(data->mlx->win, KeyRelease, KeyReleaseMask, key_release, data->mlx);
	mlx_hook(data->mlx->win, ButtonPress, ButtonPressMask, mouse_press, data->mlx);
	mlx_hook(data->mlx->win, ButtonRelease, ButtonReleaseMask, mouse_release, data->mlx);
	mlx_hook(data->mlx->win, DestroyNotify, StructureNotifyMask, exit_cub3d, data);
	mlx_loop_hook(data->mlx->mlx, &render, data);
	mlx_loop(data->mlx->mlx);
}
