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

void	write_line(int fd, char *prefix, char *str, char *suffix)
{
	if (write(fd, prefix, ft_strlen(prefix)) == -1)
		return ;
	if (write(fd, str, ft_strlen(str)) == -1)
		return ;
	if (write(fd, suffix, ft_strlen(suffix)) == -1)
		return ;
}

void	write_map_line(int fd, t_edata *data, int i)
{
	char	*line;
	int	j;

	j = -1;
	line = allocate(sizeof(char) * (data->grid_len + 1), &data->gc);
	while (++j < data->grid_len)
	{
		if (data->grid[i].state == 1)
			line[j] = '1';
		else if (data->grid[i].state == 2)
			line[j] = '0';
		else if (data->grid[i].state == 0)
			line[j] = ' ';
		i++;
	}
	line[j] = 0;
	if (write(fd, line, data->grid_len + 1) == -1)
		printf("failed\n");
	if (write(fd, "\n", 1) == -1)
		printf("failed\n");
	deallocate(line, &data->gc);
}

void	save_file(t_edata *data)
{
	int	fd;

	if (!test.state)
		return ;
	if (test.state == 2 && data->save_validate.state != 1)
	{
		update_button(&data->save_validate, 1, data->mlx);
		update_txtbox(&data->file_name, data->mlx);
		draw_button(data->save_validate, data->mlx);
		draw_txtbox(data->file_name, data->mlx);
		return ;
	}
	if (data->save_validate.state == 1)
	{
		fd = open(data->file_name.txt, O_RDWR | O_CREAT | O_APPEND, 0644);
		write_line(fd, "NO ", data->txt[0].txt, "\n");
		write_line(fd, "SO ", data->txt[1].txt, "\n");
		write_line(fd, "WE ", data->txt[2].txt, "\n");
		write_line(fd, "EA ", data->txt[3].txt, "\n\n");
		write_line(fd, "F ", data->txt[4].txt, "\n");
		write_line(fd, "C ", data->txt[5].txt, "\n\n");
		for (int i = 0; i < data->grid_size; i += data->grid_len)
			write_map_line(fd, data, i);
		close(fd);
		test.state = 0;
		data->save_validate.state = 0;
	}
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
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->frame_buffer.img, 0, 0);
	draw_button(test, data->mlx);
	c.i = -1;
	while (++c.i < 6)
		draw_txtbox(data->txt[c.i], data->mlx);
	save_file(data);
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
	data->file_name = get_txtbox((t_rec){(WIN_W/2)-150, (WIN_H/2)-13, 300, 25}, "Please enter the file path and name");
	data->save_validate = get_button((t_rec){(WIN_W/2)-150, (WIN_H/2)+100, 300, 50}, "ceci est un test", PUSH);
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
	data.mlx = mlx;
	test = get_button((t_rec){20, 600, 300, 50}, "ceci est un test", TOGGLE);
	start_mlxctx(data.mlx, render, exit_cub_editor, &data);
}
