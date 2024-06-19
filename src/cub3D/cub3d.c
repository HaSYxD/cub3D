/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:03:30 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/07 01:03:32 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	res = 2;

void	draw_minimap(t_cdata *data)
{
	int	xscale;
	int	yscale;

	xscale = (WIN_W/6) / (data->map_size.x * (WIN_H / 451));
	yscale = (WIN_H/6) / (data->map_size.y * (WIN_H / 451));
	int	r_num = WIN_W/res;
	float	fov = M_PI/3;
	double	dangle = fov / r_num;
	double	r_angle = data->p_angle - (fov/2) + 0.0001;
	for (int i = 0; i < r_num; i++){
		double sin_a = sin(r_angle);
		double cos_a = cos(r_angle);
		//hor
		float	y_hor;
		float	dy;
		if (sin_a > 0){
			y_hor = (int)data->p_pos.y + 1;
			dy = 1;
		}
		else{
			y_hor = (int)data->p_pos.y - 0.000001;
			dy = -1;
		}
		float	depth_hor = (y_hor - data->p_pos.y) / sin_a;
		float	x_hor = data->p_pos.x + depth_hor * cos_a;

		float	delta_depth = dy/sin_a;
		float	dx = delta_depth * cos_a;
		for (int i = 0; i < 15; i++){
			t_vec2	tile_hor = (t_vec2){x_hor, y_hor};
			if (check_player_to_map_collision(data->map, data->map_size, tile_hor))
				break ;
			x_hor+=dx;
			y_hor+=dy;
			depth_hor+=delta_depth;
		}
		//vert
		float	x_vert;
		if (cos_a > 0){
			x_vert = (int)data->p_pos.x + 1;
			dx = 1;
		}
		else{
			x_vert = (int)data->p_pos.x - 0.000001;
			dx = -1;
		}
		float	depth_vert = (x_vert - data->p_pos.x) / cos_a;
		float	y_vert = data->p_pos.y + depth_vert * sin_a;

		delta_depth = dx/cos_a;
		dy = delta_depth * sin_a;
		for (int i = 0; i < 15; i++){
			t_vec2	tile_vert = (t_vec2){x_vert, y_vert};
			if (check_player_to_map_collision(data->map, data->map_size, tile_vert)){
				break ;
			}
			x_vert+=dx;
			y_vert+=dy;
			depth_vert+=delta_depth;
		}
		float	depth;
		if (depth_vert < depth_hor)
			depth = depth_vert;
		else
			depth = depth_hor;
		depth *= cos(data->p_angle - r_angle);
		// line_to_fbuff(data->mlx, (t_vec2){(int)(data->p_pos.x*xscale), (int)(data->p_pos.y*yscale)},
		// 	(t_vec2){(data->p_pos.x*xscale) + (depth*xscale) * cos(r_angle),
		// 		(data->p_pos.y*yscale) + (depth*yscale) * sin(r_angle)}, (t_color){55, 255, 255, 255});
		double screen_dist = (WIN_W/2) / tan(fov/2);
		float	proj_height = screen_dist / (depth + 0.0001);
		t_color c = {255, 255 / (1+pow(depth, 5) * 0.00002), 255 / (1+pow(depth, 5) * 0.00002), 255 / (1+pow(depth, 5) * 0.00002)};
		square_to_fbuff(data->mlx, (t_rec){i*res, (WIN_H/2) - (int)proj_height / 2, res, proj_height}, c);
		r_angle += dangle;
	}
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
	}
	else if (is_key_down(data->mlx, XK_Down)){
		res++;
		if (res > 30)
			res = 30;
	}
	player_move(data);
	square_to_fbuff(data->mlx, (t_rec){0, 0, WIN_W, WIN_H/2}, data->map_col[0]);
	square_to_fbuff(data->mlx, (t_rec){0, WIN_H/2, WIN_W, WIN_H/2}, data->map_col[1]);
	// mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->minimap.img, 0, 0);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->frame_buffer.img, 0, 0);
	// usleep(50000);
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
