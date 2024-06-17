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

# define MSIZE	10

const char	map[MSIZE][MSIZE] = {
	{' ', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1', '1'},
	{'1', '0', '0', '1', '1', '1', '1', '0', '1', ' '},
	{'1', '0', '0', '1', '0', '0', '1', '0', '1', '1'},
	{'1', '0', '0', '1', '0', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '1', '0', 'N', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '1', '1', '1', '0', '0', '0', '1'},
	{'1', '1', '1', '1', ' ', '1', '1', '1', '1', '1'}
};

t_vec2	ppos;

void	draw_minimap(t_cdata *data)
{
	int	scale;

	scale = (WIN_H/4) / (MSIZE * (WIN_H / 451));
	square_to_fbuff(data->mlx, (t_rec){0, 0, scale*MSIZE, scale*MSIZE}, (t_color){255, 0, 0, 30});
	for (int i = 0; i < MSIZE; i++){
		for (int j = 0; j < MSIZE; j++){
			if (map[j][i] == '1')
				square_to_fbuff(data->mlx, (t_rec){i*scale, j*scale, scale-1, scale-1}, (t_color){255, 0, 0, 255});
			else if (map[j][i] == '0')
				square_to_fbuff(data->mlx, (t_rec){i*scale, j*scale, scale-1, scale-1}, (t_color){255, 0, 0, 55});
		}
	}
	circle_to_fbuff(data->mlx, (t_vec2){(ppos.x*scale)+scale*0.5, (ppos.y*scale)+scale*0.5}, scale*0.25, (t_color){255, 255, 0, 0});
}
static void	player_move(t_mlxctx *mlx)
{
	t_vec2	d;

	d = (t_vec2){0, 0};
	if (mlx->key_state[1] == XK_w)
		d.y -= 0.01;
	else if (mlx->key_state[1] == XK_s)
		d.y += 0.01;
	if (mlx->key_state[1] == XK_d)
		d.x += 0.01;
	else if (mlx->key_state[1] == XK_a)
		d.x -= 0.01;
	if ((ppos.x + d.x) > 0 && (ppos.x + d.x) < MSIZE-1)
		ppos.x += d.x;
	if ((ppos.y + d.y) > 0 && (ppos.y + d.y) < MSIZE-1)
		ppos.y += d.y;
}

int	res = 2;
static int	render(t_cdata *data)
{

	if (data->mlx->key_state[1] == XK_Up){
		res--;
		if (res < 1)
			res = 1;
	}
	else if (data->mlx->key_state[1] == XK_Down){
		res++;
		if (res > 30)
			res = 30;
	}
	player_move(data->mlx);
	// square_to_fbuff(data->mlx, (t_rec){0, 0, WIN_W, WIN_H/2}, (t_color){255, 255, 0, 0});
	// square_to_fbuff(data->mlx, (t_rec){0, WIN_H/2, WIN_W, WIN_H/2}, (t_color){255, 0, 255, 0});
	// for (int i = 0; i < WIN_W/res; i++)
		// square_to_fbuff(data->mlx, (t_rec){i*res, WIN_H/4, res, WIN_H/2}, (t_color){255, 255-i*res, 255-i*res, 255-i*res});
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->frame_buffer.img, 0, 0);
	print_fps_to_consol();
	return (0);
}

int	exit_cub3d(t_cdata *data)
{
	destroy_mlxctx(data->mlx);
	exit(0);
}

void	run_cub3d(t_mlxctx *mlx)
{
	t_cdata	data;

	data.mlx = mlx;
	for (int i = 0; i < MSIZE; i++)
		for (int j = 0; j < MSIZE; j++)
			if (map[j][i] == 'N')
				ppos = (t_vec2){i, j};
	mlx_hook(mlx->win, KeyPress, KeyPressMask, key_press, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, key_release, mlx);
	mlx_hook(mlx->win, ButtonPress, ButtonPressMask, mouse_press, mlx);
	mlx_hook(mlx->win, ButtonRelease, ButtonReleaseMask, mouse_release, mlx);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, exit_cub3d, &data);
	mlx_loop_hook(mlx->mlx, &render, &data);
	mlx_loop(mlx->mlx);
}
