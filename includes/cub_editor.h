/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_editor.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:39:46 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/16 22:40:11 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_EDITOR_H
# define CUB_EDITOR_H

//APP SETTINGS------------//
# define WIN_W	1600
# define WIN_H	900
# define WIN_N	"cub3D"
//------------------------//

//DEPENDENCIES------------//
# include <X11/keysym.h>
# include <X11/X.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>

# include <cub_framework.h>
//------------------------//

//GENERAL DATAS-----------//
typedef struct s_data_ed
{
	t_garb		gc;
	t_mlxctx	*mlx;
	t_txtbox	txt[6];
	t_button	*grid;
	int			grid_size;
	int			grid_len;
}	t_data_ed;
//general cub3D datas
//------------------------//

void	run_editor(t_mlxctx *mlx, char *argv[]);

#endif
