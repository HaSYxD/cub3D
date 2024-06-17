/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afromont <afromont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:03:36 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/17 16:35:41 by afromont         ###   ########.fr       */
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
# include <cub_framework.h>
//------------------------//

//GENERAL DATAS-----------//
typedef struct s_cdata
{
	t_mlxctx	*mlx;
	t_garb	gc;
	t_vec2	p_pos;
	double	p_angle;
	t_color	map_col[2];
	char	(*wall_tex[4]);
	t_vec2	map_size;
	char	**map;
}	t_cdata;
//general cub3D datas
//------------------------//

void	run_cub3d(t_mlxctx *mlx);

int ft_errorarg(char **agv, int argc);

int	ft_cparsing(char **agv, t_garb *gc, t_cdata *cdata);

//int	ft_eparsing(char **agv, t_garb *gc, t_edata *edata);

#endif
