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

# include "cub3d_int.h"
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
	int	key_state[2];
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
void	square_to_fbuff(t_img *fbuff, t_rec rec, t_color col);
void	pixel_to_fbuff(t_img *fbuff, t_vec2 pos, t_color col);
void	image_to_fbuff(t_img *fbuff, t_img *img, t_vec2 size, t_vec2 pos);
//drawing functions

void	print_fps_to_consol(void);
//monitoring functions

int	check_collision_point_rec(t_rec rec, t_vec2 point);
//collision functions

t_button	get_button(t_rec body, char *title, int type);
void			update_button(t_button *button, int new_state, t_data *data);
void			draw_button(t_button button, t_data *data);
t_txtbox	get_txtbox(t_rec body, char *title);
void			update_txtbox(t_txtbox *txtbox, t_data *data);
void			draw_txtbox(t_txtbox txtbox, t_data *data);
//ui functions

int	mouse_press(int mouse_code, int x, int y, t_data *data);
int	mouse_release(int mouse_code, int x, int y, t_data *data);
int	key_press(int key_code, t_data *data);
int	key_release(int key_code, t_data *data);
//input	handlingfunctions
//------------------------//

#endif
