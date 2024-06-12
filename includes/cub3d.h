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
# include <X11/keysym.h>
# include <X11/X.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>
//------------------------//

//FRAMEWORK TYPES---------//

# define MLX_RED	(struct s_color){255, 255, 0, 0}
# define MLX_GREEN	(struct s_color){255, 0, 255, 0}
# define MLX_BLUE	(struct s_color){255, 0, 0, 255}
# define MLX_WHITE	(struct s_color){255, 255, 255, 255}
# define MLX_LGRAY	(struct s_color){255, 150, 150, 150}
# define MLX_DGRAY	(struct s_color){255, 50, 50, 50}
# define MLX_BLACK	(struct s_color){255, 0, 0, 0}

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

typedef struct s_rec
{
	float	x;
	float	y;
	int	width;
	int	height;
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

typedef struct s_button
{
	t_rec	body;
	int	state;
}	t_button;
//------------------------//

//GENERAL DATAS-----------//
typedef struct s_data
{
	t_img	creeper;
	t_img	frame_buffer;
	void	*mlx;
	void	*win;
	size_t	s_time;
	t_vec2	mouse_position;
	int	mouse_state;
}	t_data;
//general cub3D datas
//------------------------//
void	editor_loop(t_data *data, char *argv[]);


//FRAMEWORK FUNTIONS------//
t_color	int_to_color(int col);
int		color_to_int(t_color col);
//colors functions

float	vec2_dst(t_vec2 point, t_vec2 c_pos);
//math functions

void	circle_to_fbuff(t_img *fbuff, t_vec2 pos, float radius, t_color col);
void	square_to_fbuff(t_img *fbuff, t_vec2 pos, t_vec2 size, t_color col);
void	pixel_to_fbuff(t_img *fbuff, t_vec2 pos, t_color col);
void	image_to_fbuff(t_img *fbuff, t_img *img, t_vec2 size, t_vec2 pos);
//drawing functions

void	print_fps_to_consol(void);
//monitoring functions

int	check_collision_point_rec(t_rec rec, t_vec2 point);
//collision functions

t_button	get_button(t_rec body);
void			update_button(t_button *button, int new_state, t_data *data);
void			draw_button(t_button button, t_data *data);
//ui functions
//------------------------//

#endif
