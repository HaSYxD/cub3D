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

static int	cub_exit(t_data *data, int exit_status)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		ft_free(data->mlx);
	}
	exit (exit_status);
}

static int	cub_init(t_data *data)
{
	int	init_status;

	init_status = 0;
	data->mlx = mlx_init();
	if (!data->mlx)
		init_status = EXIT_FAILURE;
	if (init_status != EXIT_FAILURE)
		data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, WIN_N);
	if (!data->win)
		init_status = EXIT_FAILURE;
	return (init_status);
}

int	main(void)
{
	t_data	data;

	data = (t_data){0};
	if (cub_init(&data) != 0)
		cub_exit(&data, EXIT_FAILURE);

	/*int	w = 800;
	int	h = 600;

	void	*img = mlx_xpm_file_to_image(data.mlx, "./assets/creeper.xpm", &w, &h);
	if (!img)
		return (1);
	mlx_put_image_to_window(data.mlx, data.win, img, 0, 0);*/

	//***Retire la loop pour check les leak sans ctrl-c***
	mlx_loop(data.mlx);
	cub_exit(&data, 0);
}
