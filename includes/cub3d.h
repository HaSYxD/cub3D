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
	//raycasting parameters
	t_vec2	smallest_wall;
	double	fov;
	double	delta_angle;
	uint8_t	draw_distance;
	uint8_t	render_res;
	uint16_t	ray_num;

	//context and memory management
	t_mlxctx	*mlx;
	t_garb	gc;

	//player
	t_vec2	p_pos;
	double	p_angle;

	//map
	t_img	minimap;
	t_color	map_col[2];
	char	(*wall_tex[4]);
	t_img	wall_tex_img[4];
	t_vec2	map_size;
	char	**map;

	//parsing
	char	**texture;
}	t_cdata;
//general cub3D datas
//------------------------//

t_color	compute_wall_fog(t_color fog_col, t_color wall_col, double depth, uint8_t draw_dst);
t_color	compute_floor_fog(t_color fog_col, t_color floor_col, float depth);
void	draw_minimap(t_cdata *data);
void	draw_background(t_cdata *data);
void	draw_wall_segment(t_cdata *data, int i, double depth, t_color base_col);
//rendering functions

double	get_vert_travel(t_cdata *data, t_vec2 cossin_a);
double	get_hor_travel(t_cdata *data, t_vec2 cossin_a);
void	raycasting(t_cdata *data);
//raycasting functions

void	run_cub3d(t_cdata *data);

int	check_player_to_map_collision(char **map, t_vec2 msize, t_vec2 dpos);
int	check_ray_to_map_collision(char **map, t_vec2 msize, t_vec2 dpos);

void	player_move(t_cdata *data);

int ft_errorarg(char **agv, int argc);

int	ft_cparsing(char **agv, t_garb *gc, t_cdata *cdata);

//int	ft_eparsing(char **agv, t_garb *gc, t_edata *edata);

#endif
