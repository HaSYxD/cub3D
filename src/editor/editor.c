/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:43:14 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/13 11:43:16 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub_editor.h>

t_button	test;

static void	fill_grid(int i, t_edata *data)
{
	int	grid_size;
	int	grid_len;

	grid_size = data->grid_size;
	grid_len = data->grid_len;
	data->grid[i].state = 2;
	if (i > 0 && data->grid[i - 1].state == 0)
		return (fill_grid(i - 1, data));
	if (i < grid_size && data->grid[i + 1].state == 0)
		return (fill_grid(i + 1, data));
	if (i > grid_len && data->grid[i - grid_len].state == 0)
		return (fill_grid(i - grid_len, data));
	if (i < (grid_size - grid_len) && data->grid[i + grid_len].state == 0)
		return (fill_grid(i + grid_len, data));
}

int	gridmod = 1;

static int	render(t_edata *data)
{
	t_count	c;

	c = (t_count){-1, 0, 0};
	mlx_mouse_get_pos(data->mlx->mlx, data->mlx->win, &c.j, &c.k);
	data->mlx->mouse_position = (t_vec2){c.j, c.k};
	while (++c.i < data->grid_size)
	{
		if (c.i < 6)
			update_txtbox(&data->txt[c.i], data->mlx);
		update_button(&data->grid[c.i], gridmod, data->mlx);
		if (data->grid[c.i].state == 2 && data->mlx->mouse_state == 1)
			fill_grid(c.i, data);
	}
	update_button(&test, 2, data->mlx);
	if (test.state == 2)
		gridmod = 2;
	c.i = -1;
	while (++c.i < data->grid_size)
		draw_button(data->grid[c.i], data->mlx);
	draw_button(test, data->mlx);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->frame_buffer.img, 0, 0);
	c.i = -1;
	while (++c.i < 6)
		draw_txtbox(data->txt[c.i], data->mlx);
	print_fps_to_consol(data->mlx);
	return (0);
}

int	exit_cub_editor(t_edata *data)
{
	destroy_mlxctx(data->mlx);
	clean_garbage(&data->gc);
	exit(0);
}

int	init_cub_editor(t_edata *data, char *argv[])
{
	t_count	c;

	data->gc = (t_garb){NULL, 0};
	data->grid_len = ft_atoi(argv[2]);
	data->grid_size = (int)pow(data->grid_len, 2);
	c = (t_count){-1, WIN_H / (data->grid_len * (WIN_H / 451)),
		(WIN_W - WIN_H) / 2};
	if (data->grid_len < 5 || data->grid_len > 40)
		return (printf("Map size must be between 5 and 40 square wide\n"), -1);
	data->grid = allocate(sizeof(t_button) * data->grid_size, &data->gc);
	while (++c.i < data->grid_size)
		data->grid[c.i] = get_button((t_rec){(c.i % data->grid_len * c.j) + c.k,
				(c.i / data->grid_len * c.j), c.j - 1, c.j - 1}, "", TOGGLE);
	data->txt[0] = get_txtbox((t_rec){20, 50, 300, 25}, "North Texture Path");
	data->txt[1] = get_txtbox((t_rec){20, 125, 300, 25}, "South Texture Path");
	data->txt[2] = get_txtbox((t_rec){20, 200, 300, 25}, "West Texture Path");
	data->txt[3] = get_txtbox((t_rec){20, 275, 300, 25}, "East Texture Path");
	data->txt[4] = get_txtbox((t_rec){20, 400, 300, 25}, "Floor RGB color");
	data->txt[5] = get_txtbox((t_rec){20, 475, 300, 25}, "Ceilling RGB color");
	return (0);
}

void	run_editor(t_mlxctx *mlx, char *argv[])
{
	t_edata	data;

	if (init_cub_editor(&data, argv) != 0)
	{
		destroy_mlxctx(mlx);
		return ;
	}
	printf("%ld\n", sizeof(t_mlxctx *));
	data.mlx = mlx;
	test = get_button((t_rec){20, 600, 300, 50}, "ceci est un test", PUSH);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, key_press, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, key_release, mlx);
	mlx_hook(mlx->win, ButtonPress, ButtonPressMask, mouse_press, mlx);
	mlx_hook(mlx->win, ButtonRelease, ButtonReleaseMask, mouse_release, mlx);
	mlx_loop_hook(mlx->mlx, &render, &data);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, exit_cub_editor, &data);
	mlx_loop(mlx->mlx);
}
