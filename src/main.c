/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afromont <afromont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:39:17 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/21 15:06:09 by afromont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub_editor.h>
#include <cub3d.h>

int	main(int argc, char *argv[])
{
	t_mlxctx	mlx;
	t_cdata		cdata;
	//t_edata		edata;

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
		//else if (argc == 3)
		//ft_eparsing(argv, &parsgc, &edata);
		if (init_mlxctx(&mlx, WIN_W, WIN_H, WIN_N) != 0)
			destroy_mlxctx(&mlx);
		cdata.mlx = &mlx;
		if ((ft_strncmp(argv[1], "EDITOR", 6) == 0) && argc == 3)
			run_editor(&mlx, argv);
		else if ((ft_strncmp(argv[1], "EDITOR", 6) != 0) && argc == 2)
			run_cub3d(&cdata);
	}
	return (0);
}
