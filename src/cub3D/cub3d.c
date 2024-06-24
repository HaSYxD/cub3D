/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:03:30 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/21 17:15:03 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_vec2	creeper_size;

int	exit_cub3d(t_cdata *data)
{
	mlx_destroy_image(data->mlx->mlx, data->minimap.img);
	destroy_mlxctx(data->mlx);
	clean_garbage(&data->gc);
	exit(0);
}

static int	render(t_cdata *data)
{
	static int	door_tick = 0;
	if (is_key_down(data->mlx, XK_Escape))
		exit_cub3d(data);
	if (is_key_down(data->mlx, XK_Up))
	{
		data->render_res--;
		if (data->render_res < 1)
			data->render_res = 1;
	}
	else if (is_key_down(data->mlx, XK_Down))
	{
		data->render_res++;
		if (data->render_res > 20)
			data->render_res = 20;
	}
	player_move(data);
	draw_background(data);
	raycasting(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->frame_buffer.img, 0, 0);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->wall_tex_img[0].img, 0, 0);
	print_fps_to_consol(data->mlx);
	door_tick++;
	return (0);
}

void	compute_minimap(t_cdata *data)
{
	t_count	c;
	int		xscale;
	int		yscale;

	c = (t_count){-1, -1, 0};
	xscale = (data->map_size.x * 10) / (data->map_size.x * (WIN_H / 451));
	yscale = (data->map_size.y * 10) / (data->map_size.y * (WIN_H / 451));
	data->minimap.img = mlx_new_image(data->mlx->mlx, data->map_size.x*10, data->map_size.y*10);
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
	image_to_fbuff(&data->minimap, &data->mlx->frame_buffer, (t_vec2){WIN_W, WIN_H}, (t_vec2){0, 0});
}



void	run_cub3d(t_cdata *data)
{
	data->fov = M_PI / 3;
	data->draw_distance = 20;
	data->render_res = 8;
	data->smallest_wall = (t_vec2){WIN_H / 2, 0};
	data->wall_tex_img[0] = load_xpm(data->mlx, data->wall_tex[0], &creeper_size);
	data->wall_tex_img[1] = load_xpm(data->mlx, data->wall_tex[1], &creeper_size);
	data->wall_tex_img[2] = load_xpm(data->mlx, data->wall_tex[2], &creeper_size);
	data->wall_tex_img[3] = load_xpm(data->mlx, data->wall_tex[3], &creeper_size);
	compute_minimap(data);
	start_mlxctx(data->mlx, render, exit_cub3d, data);
}
