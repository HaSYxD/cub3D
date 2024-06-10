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
# include <math.h>
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

typedef struct s_color
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;
//------------------------//

//GENERAL DATAS-----------//
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_data
{
	t_img	frame_buffer;
	void	*mlx;
	void	*win;
}	t_data;
//------------------------//

t_color	int_to_color(int col);

float	vec2_dst(t_vec2 point, t_vec2 c_pos);

void	circle_to_fbuff(t_img *fbuff, t_vec2 pos, float radius, t_color col);
void	square_to_fbuff(t_img *fbuff, t_vec2 pos, t_vec2 size, t_color col);
void	pixel_to_fbuff(t_img *fbuff, t_vec2 pos, t_color col);
void	image_to_fbuff(t_img *fbuff, t_img *img, t_vec2 size, t_vec2 pos);
int		color_to_int(t_color col);

#endif
