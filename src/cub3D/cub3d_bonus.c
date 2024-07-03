/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afromont <afromont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:03:30 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/25 13:18:57 by afromont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	exit_cub3d(t_cdata *data)
{
	mlx_destroy_image(data->mlx->mlx, data->minimap.img);
	mlx_destroy_image(data->mlx->mlx, data->wall_tex_img[0].img);
	mlx_destroy_image(data->mlx->mlx, data->wall_tex_img[1].img);
	mlx_destroy_image(data->mlx->mlx, data->wall_tex_img[2].img);
	mlx_destroy_image(data->mlx->mlx, data->wall_tex_img[3].img);
	destroy_mlxctx(data->mlx);
	clean_garbage(&data->gc);
	exit(0);
}

static void	render_game(t_cdata *data)
{
	draw_background(data);
	raycasting(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->frame_buffer.img, 0, 0);
}

static int	update(t_cdata *data)
{
	if (is_key_pressed(data->mlx, XK_Escape))
		exit_cub3d(data);
	render_game(data);
	mouse_control(data);
	player_move(data);
	print_fps_to_consol(data->mlx);
	return (0);
}

void	compute_minimap(t_cdata *data, t_count c)
{
	data->minimap.img = mlx_new_image(data->mlx->mlx,
			data->map_size.x * 10, data->map_size.y * 10);
	data->minimap.addr = mlx_get_data_addr(data->minimap.img,
			&data->minimap.bpp, &data->minimap.line_length,
			&data->minimap.endian);
	square_to_fbuff(data->mlx, (t_rec){0, 0,
		data->minim_scale.x * data->map_size.x,
		data->minim_scale.y * data->map_size.y}, (t_color){255, 0, 0, 30});
	while (++c.i < data->map_size.y)
	{
		while (++c.j < data->map_size.x)
		{
			if (data->map[c.i][c.j] == '1')
				square_to_fbuff(data->mlx, (t_rec){c.j * data->minim_scale.x,
					c.i * data->minim_scale.y, data->minim_scale.x - 1,
					data->minim_scale.y - 1}, (t_color){255, 0, 0, 255});
			else if (data->map[c.i][c.j] == '0')
				square_to_fbuff(data->mlx, (t_rec){c.j * data->minim_scale.x,
					c.i * data->minim_scale.y, data->minim_scale.x - 1,
					data->minim_scale.y - 1}, (t_color){255, 0, 0, 55});
		}
		c.j = -1;
	}
	image_to_fbuff(&data->minimap, &data->mlx->frame_buffer,
		(t_vec2){WIN_W, WIN_H}, (t_vec2){0, 0});
}

void	run_cub3d(t_cdata *data)
{
	data->img_size = 0;
	data->fov = M_PI / 3;
	data->draw_distance = 20;
	data->render_res = RENDER_RES;
	data->smallest_wall = (t_vec2){WIN_H / 2, 0};
	data->state = MOUSE_ENABLE;
	data->vert_shading = DEF_VERT_SHADE;
	data->hor_shading = DEF_HOR_SHADE;
	data->minim_scale.x = (data->map_size.x * 10)
		/ (data->map_size.x * (WIN_H / 451));
	data->minim_scale.y = (data->map_size.y * 10)
		/ (data->map_size.y * (WIN_H / 451));
	data->wall_tex_img[0] = load_xpm(data->mlx,
			data->wall_tex[0], &data->img_size);
	data->wall_tex_img[1] = load_xpm(data->mlx,
			data->wall_tex[1], &data->img_size);
	data->wall_tex_img[2] = load_xpm(data->mlx,
			data->wall_tex[2], &data->img_size);
	data->wall_tex_img[3] = load_xpm(data->mlx,
			data->wall_tex[3], &data->img_size);
	data->fog_col = data->map_col[0];
	compute_minimap(data, (t_count){-1, -1, 0});
	mlx_mouse_hide(data->mlx->mlx, data->mlx->win);
	start_mlxctx(data->mlx, update, exit_cub3d, data);
}
