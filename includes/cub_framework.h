/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_framework.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:40:21 by aliaudet          #+#    #+#             */
/*   Updated: 2024/07/02 18:44:30 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_FRAMEWORK_H
# define CUB_FRAMEWORK_H

//DEPENDENCIES------------//
# include <X11/keysym.h>
# include <stdint.h>
# include <libft.h>
# include <X11/X.h>
# include <math.h>
# include <mlx.h>
//------------------------//

//FRAMEWORK TYPES---------//
# define MLX_RED	0xFFFF0000
# define MLX_GREEN	0xFF00FF00
# define MLX_BLUE	0xFF0000FF
# define MLX_WHITE	0xFFFFFFFF
# define MLX_LGRAY	0xFF969696
# define MLX_DGRAY	0xFF323232
# define MLX_BLACK	0xFF000000
//pre defined colors

# define MAX_TXTBOX_LEN	128
# define FONT	"-*-*-*-*-*-*-*-*-*-*-*-*-*-*"
//text parameters

enum	e_button_type
{
	TOGGLE,
	PUSH
};
//button types

typedef struct s_count
{
	int	i;
	int	j;
	int	k;
}	t_count;
//to use when multiple counter variales are needed (save lines)

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;
//to use when working with 2D coordonnates or sizes

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;
//to use when working with 3D coordonnates or sizes

typedef struct s_rec
{
	float	x;
	float	y;
	int		width;
	int		height;
}	t_rec;
//to use for representing any rectangle in memory

typedef struct s_color
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;
//to use when working with colors

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;
//standard components needed for mlx images

typedef struct s_txtbox
{
	t_rec	body;
	char	*title;
	char	txt[MAX_TXTBOX_LEN];
}	t_txtbox;
//for inputing text on screen

typedef struct s_button
{
	t_rec	body;
	char	*title;
	int		state;
	int		type;
}	t_button;
//interactive rectangle

typedef struct s_slidebar
{
	t_rec	body;
	t_vec2	knob_pos;
	char	*title;
	int		min_value;
	int		max_value;
	int		current_value;
}	t_slidebar;
//interactive rectangle

typedef struct s_mlxctx
{
	double	frame_time;
	t_vec2	mouse_position;
	t_img	frame_buffer;
	void	*mlx;
	void	*win;
	int		win_w;
	int		win_h;
	int		mouse_state;
	int		key_state[3];
}	t_mlxctx;
//------------------------//

//FRAMEWORK FUNTIONS------//
t_color	int_to_color(int col);
int		color_to_int(t_color col);
//colors functions

float	vec2_dst(t_vec2 point, t_vec2 c_pos);
//math functions

void	line_to_fbuff(t_mlxctx *mlx, t_vec2 p1, t_vec2 p2, t_color color);
void	circle_to_fbuff(t_mlxctx *mlx, t_vec2 pos, float radius, t_color col);
void	square_to_fbuff(t_mlxctx *mlx, t_rec rec, t_color col);
void	pixel_to_fbuff(t_mlxctx *mlx, t_vec2 pos, t_color col);
void	image_to_fbuff(t_img *fbuff, t_img *img, t_vec2 size, t_vec2 pos);
//drawing functions

void	print_fps_to_consol(t_mlxctx *mlx);
//monitoring functions

t_button	get_button(t_rec body, char *title, int type);
void	update_button(t_button *button, int new_state, t_mlxctx *mlx);
void	draw_button(t_button button, t_mlxctx *mlx);
t_txtbox	get_txtbox(t_rec body, char *title);
void	update_txtbox(t_txtbox *txtbox, t_mlxctx *mlx);
void	draw_txtbox(t_txtbox txtbox, t_mlxctx *mlx);
//ui functions

int		check_collision_point_rec(t_rec rec, t_vec2 point);
int		check_collision_point_circle(t_vec2 center, float radius, t_vec2 point);
//collision functions

void	update_mouse_pos(t_mlxctx *mlx);
int		mouse_press(int mouse_code, int x, int y, t_mlxctx *mlx);
int		mouse_release(int mouse_code, int x, int y, t_mlxctx *mlx);
int		key_press(int key_code, t_mlxctx *mlx);
int		key_release(int key_code, t_mlxctx *mlx);
int		is_key_down(t_mlxctx *mlx, int key);
int		is_key_pressed(t_mlxctx *mlx, int key);
//input	handling functions

t_img	load_xpm(t_mlxctx *mlx, char *path, int *size);
int		init_mlxctx(t_mlxctx *mlx, int w, int h, char *name);
int		destroy_mlxctx(t_mlxctx *mlx);
int		start_mlxctx(t_mlxctx *mlx, int (*start_func)(),
			int (*quit_func)(), void *param);
//mlx context handling
//------------------------//
#endif
