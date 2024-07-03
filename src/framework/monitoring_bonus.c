/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:44:09 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/16 22:35:39 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub_framework.h>

void	print_fps_to_consol(t_mlxctx *mlx)
{
	static double	start_time = 0;
	static int		frames = 1;
	double			sec;

	if (!start_time)
		start_time = ft_gettime();
	sec = ((ft_gettime() - start_time) / 1000);
	mlx->frame_time = 1 / (frames / sec);
	if ((frames % (int)(frames / sec)) == 0)
	{
		printf("FPS :%f\n", frames / sec);
		start_time = ft_gettime();
		frames = 1;
	}
	frames++;
}
