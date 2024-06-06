/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:03:36 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/07 01:03:42 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//APP SETTINGS------------//
# define WIN_W	1600
# define WIN_H	900
# define WIN_N	"cub3D"
//------------------------//

//DEPENDENCIES------------//
# include <libft.h>
# include <mlx.h>
//------------------------//

//PARSING AND UTILS-------//
typedef struct s_count
{
	int	i;
	int	j;
	int	k;
}	t_count;
//------------------------//

//RENDERING AND STUFF-----//
typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;
//------------------------//

//GENERAL DATAS-----------//
typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*frame_buffer;
}	t_data;
//------------------------//

#endif
