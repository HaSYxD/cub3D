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

#include <cub3d.h>

t_button	*grid = NULL;
t_txtbox	txt = {0};
t_txtbox	txt2 = {0};
t_txtbox	txt3 = {0};
t_txtbox	txt4 = {0};
t_txtbox	txt5 = {0};
t_txtbox	txt6 = {0};
int	grid_size;

t_button	test;

static int	render(t_data *data)
{
	int	mx, my = 0;

	mlx_mouse_get_pos(data->mlx, data->win, &mx, &my);
	data->mouse_position = (t_vec2){mx, my};
	for (int i = 0; i < grid_size; i++) {
		update_button(&grid[i], 1, data);
	}
	update_txtbox(&txt, data);
	update_txtbox(&txt2, data);
	update_txtbox(&txt3, data);
	update_txtbox(&txt4, data);
	update_txtbox(&txt5, data);
	update_txtbox(&txt6, data);
	update_button(&test, 2, data);
	for (int i = 0; i < grid_size; i++) {
		draw_button(grid[i], data);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->frame_buffer.img, 0, 0);
	draw_txtbox(txt, data);
	draw_txtbox(txt2, data);
	draw_txtbox(txt3, data);
	draw_txtbox(txt4, data);
	draw_txtbox(txt5, data);
	draw_txtbox(txt6, data);
	draw_button(test, data);
	print_fps_to_consol();
	return (0);
}

void	editor_loop(t_data *data, char *argv[])
{
	t_count	c;
	int	scale;
	int	xoffset;

	c = (t_count){-1, ft_atoi(argv[2]), 0};
	if (c.j < 5 || c.j > 30)
	{
		printf("Map size must be between 5 and 30 square wide\n");
		return ;
	}
	grid_size = c.j * c.j;
	grid = malloc(sizeof(*grid) * grid_size);
	scale = WIN_H / (c.j * (WIN_H / 451));
	xoffset = (WIN_W - WIN_H) / 2;
	mlx_set_font(data->mlx, data->win, FONT);
	while (++c.i < grid_size)
		grid[c.i] = get_button((t_rec){(c.i%c.j*scale) + xoffset, (c.i/c.j*scale), scale-1, scale-1}, "", TOGGLE);
	test = get_button((t_rec){20, 600, 300, 50}, "ceci est un test", PUSH);
	txt = get_txtbox((t_rec){20, 50, 300, 25}, "North Texture Path");
	txt2 = get_txtbox((t_rec){20, 125, 300, 25}, "South Texture Path");
	txt3 = get_txtbox((t_rec){20, 200, 300, 25}, "West Texture Path");
	txt4 = get_txtbox((t_rec){20, 275, 300, 25}, "East Texture Path");
	txt5 = get_txtbox((t_rec){20, 400, 300, 25}, "Floor RGB color");
	txt6 = get_txtbox((t_rec){20, 475, 300, 25}, "Ceilling RGB color");
	mlx_loop_hook(data->mlx, &render, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, mouse_press, data);
	mlx_hook(data->win, ButtonRelease, ButtonReleaseMask, mouse_release, data);
	mlx_loop(data->mlx);
}
