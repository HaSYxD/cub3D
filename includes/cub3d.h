/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afromont <afromont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:03:36 by aliaudet          #+#    #+#             */
/*   Updated: 2024/07/02 22:45:06 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//APP SETTINGS------------//
# define WIN_W	1600
# define WIN_H	900
# define WIN_N	"cub3D"

# define DEF_VERT_SHADE	0
# define DEF_HOR_SHADE	8
# define RENDER_RES	2
//------------------------//

//DEPENDENCIES------------//
# include <cub_framework.h>
//------------------------//

//GENERAL DATAS-----------//
enum	e_mouse_state
{
	MOUSE_ENABLE,
	MOUSE_DISABLE
};

enum	e_raydir
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

typedef struct s_cdata
{
	//raycasting parameters
	uint16_t	ray_num;
	uint8_t		draw_distance;
	uint8_t		render_res;
	t_vec2		smallest_wall;
	double		fov;
	double		delta_angle;
	double		vert_tex_offset;
	double		hor_tex_offset;

	//rendering datas
	uint8_t		vert_shading;
	uint8_t		hor_shading;
	t_color		fog_col;
	t_color		map_col[2];
	t_img		wall_tex_img[4];
	int			img_size;

	//context and memory management
	t_mlxctx	*mlx;
	uint8_t		state;
	t_garb		gc;

	//player
	t_vec2		p_pos;
	double		p_angle;

	//map
	t_vec2		map_size;
	t_vec2		minim_scale;
	t_img		minimap;
	char		(*wall_tex[4]);
	char		**map;

	//parsing
	char		**texture;
}	t_cdata;
//general cub3D datas
//------------------------//

t_color	compute_wall_fog(t_color fog_col, t_color wall_col,
			double depth, uint8_t draw_dst);
t_color	compute_floor_fog(t_color fog_col, t_color floor_col, float depth);
void	draw_minimap(t_cdata *data);
void	draw_background(t_cdata *data);
void	draw_wall_segment(t_cdata *data, int i, double depth, int dir);
t_color	select_basecolor(t_cdata *data, double depth, int dir, int y);
//rendering functions

double	get_vert_travel(t_cdata *data, t_vec2 cossin_a,
			t_vec3 values, int *raydir);
double	get_hor_travel(t_cdata *data, t_vec2 cossin_a,
			t_vec3 values, int *raydir);
void	raycasting(t_cdata *data);
//raycasting functions

void	run_cub3d(t_cdata *data);
void	mouse_control(t_cdata *data);
//generals functions

void	player_move(t_cdata *data);
int		check_player_to_map_collision(char **map, t_vec2 msize, t_vec2 dpos);
int		check_ray_to_map_collision(char **map, t_vec2 msize, t_vec2 dpos);
//player related functions

void	ft_initextures(t_cdata *cdata);
char	*extendmap(char *str, int len, t_garb *gc);
int		ft_errorarg(char **agv, int argc);
int		ft_cparsing(char **agv, t_garb *gc, t_cdata *cdata);
int		ft_map(t_garb *gc, t_cdata *cdata);
int		ft_textures(t_garb *gc, t_cdata *cdata);
int		ft_errorarg(char **agv, int ac);
int		isplayer(const char c);
int		outmap(const char c);
//parsing functions

//int	ft_eparsing(char **agv, t_garb *gc, t_edata *edata);

#endif
