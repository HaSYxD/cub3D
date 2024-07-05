/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afromont <afromont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:39:17 by aliaudet          #+#    #+#             */
/*   Updated: 2024/07/04 14:35:56 by afromont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char *argv[])
{
	t_mlxctx	mlx;
	t_cdata		cdata;

	cdata.gc = (t_garb){NULL, 0};
	if (argc >= 2)
	{
		if (ft_errorarg(argv, argc) != 0)
			return (1);
		if (argc == 2 && ft_cparsing(argv, &cdata.gc, &cdata) != 0)
		{
			clean_garbage(&cdata.gc);
			return (1);
		}
		if (init_mlxctx(&mlx, WIN_W, WIN_H, WIN_N) != 0)
			destroy_mlxctx(&mlx);
		cdata.mlx = &mlx;
		run_cub3d(&cdata);
	}
	else
		return (printf("Please enter the .cub file\n"), 1);
	return (0);
}
