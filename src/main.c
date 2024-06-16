/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:39:17 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/16 22:39:19 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub_editor.h>
#include <cub3d.h>

int	main(int argc, char *argv[])
{
	t_mlxctx	mlx;

	if (argc >= 2)
	{
		if (init_mlxctx(&mlx, WIN_W, WIN_H, WIN_N) != 0)
			destroy_mlxctx(&mlx);
		if ((ft_strncmp(argv[1], "EDITOR", 6) == 0) && argc == 3)
			run_editor(&mlx, argv);
		else if ((ft_strncmp(argv[1], "EDITOR", 6) != 0) && argc == 2)
			run_cub3d(&mlx);
	}
	return (0);
}
