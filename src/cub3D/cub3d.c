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
	t_count	c;
	int	xscale;
	int	yscale;

	c = (t_count){-1, -1, 0};
	xscale = (WIN_W/2) / (data->map_size.x * (WIN_H / 451));
	yscale = (WIN_H/2) / (data->map_size.y * (WIN_H / 451));
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
	int	r_num = WIN_W/res;
	float	fov = M_PI/2;
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
		line_to_fbuff(data->mlx, (t_vec2){(int)(data->p_pos.x*xscale), (int)(data->p_pos.y*yscale)},
			(t_vec2){(data->p_pos.x*xscale) + (depth*xscale) * cos(r_angle),
				(data->p_pos.y*yscale) + (depth*yscale) * sin(r_angle)}, (t_color){55, 255, 255, 255});
		r_angle += dangle;
	}
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
	square_to_fbuff(data->mlx, (t_rec){0, 0, WIN_W, WIN_H/2}, (t_color){255, 255, 0, 0});
	square_to_fbuff(data->mlx, (t_rec){0, WIN_H/2, WIN_W, WIN_H/2}, (t_color){255, 0, 255, 0});
	// for (int i = 0; i < WIN_W/res; i++)
		// square_to_fbuff(data->mlx, (t_rec){i*res, WIN_H/4, res, WIN_H/2}, (t_color){255, 255-i*res, 255-i*res, 255-i*res});
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->frame_buffer.img, 0, 0);
	// usleep(50000);
	print_fps_to_consol(data->mlx);
	return (0);
}

void	run_cub3d(t_cdata *data)
{
	for (int i = 0; i < data->map_size.x; i++)
		for (int j = 0; j < data->map_size.y; j++)
			if (data->map[j][i] == 'N')
				data->p_pos = (t_vec2){i, j};
	data->p_angle = -(M_PI/2);
	mlx_hook(data->mlx->win, KeyPress, KeyPressMask, key_press, data->mlx);
	mlx_hook(data->mlx->win, KeyRelease, KeyReleaseMask, key_release, data->mlx);
	mlx_hook(data->mlx->win, ButtonPress, ButtonPressMask, mouse_press, data->mlx);
	mlx_hook(data->mlx->win, ButtonRelease, ButtonReleaseMask, mouse_release, data->mlx);
	mlx_hook(data->mlx->win, DestroyNotify, StructureNotifyMask, exit_cub3d, data);
	mlx_loop_hook(data->mlx->mlx, &render, data);
	mlx_loop(data->mlx->mlx);
}
