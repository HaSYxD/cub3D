/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:44:09 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/13 11:44:11 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	print_fps_to_consol(void)
{
	static double	start_time = 0;
	static int	frames = 1;
	double			sec;

	if (!start_time)
		start_time = ft_gettime();
	sec = ((ft_gettime() - start_time) / 1000);
	if ((frames % (int)(frames / sec)) == 0)
		printf("FPS :%f\n", frames / sec);
	frames++;
}
