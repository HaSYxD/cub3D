/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:33:56 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/18 21:33:57 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_vec2	move_vert(t_cdata *data, int dir)
{
	t_vec2	delta;
	t_vec2	dir_a;
	double	speed;

	speed = data->mlx->frame_time * 3;
	delta = (t_vec2){0, 0};
	dir_a = (t_vec2){speed * sin(data->p_angle), speed * cos(data->p_angle)};
	delta.x += dir_a.y * dir;
	delta.y += dir_a.x * dir;
	return (delta);
}

t_vec2	move_hor(t_cdata *data, int dir)
{
	t_vec2	delta;
	t_vec2	dir_a;
	double	speed;

	speed = data->mlx->frame_time * 3;
	delta = (t_vec2){0, 0};
	dir_a = (t_vec2){speed * sin(data->p_angle), speed * cos(data->p_angle)};
	delta.x += dir_a.x * (-dir);
	delta.y += dir_a.y * dir;
	return (delta);
}

void	rotate(t_cdata *data, int dir)
{
	data->p_angle += data->mlx->frame_time * (4 * dir);
	if (data->p_angle < 0)
		data->p_angle += M_PI * 2;
	if (data->p_angle > M_PI * 2)
		data->p_angle -= (M_PI * 2);
}

void	player_move(t_cdata *data)
{
	t_vec2	delta_vert;
	t_vec2	delta_hor;

	delta_vert = (t_vec2){0, 0};
	delta_hor = (t_vec2){0, 0};
	if (is_key_down(data->mlx, XK_w))
		delta_vert = move_vert(data, 1);
	else if (is_key_down(data->mlx, XK_s))
		delta_vert = move_vert(data, -1);
	if (is_key_down(data->mlx, XK_d))
		delta_hor = move_hor(data, 1);
	else if (is_key_down(data->mlx, XK_a))
		delta_hor = move_hor(data, -1);
	if (is_key_down(data->mlx, XK_Left))
		rotate(data, -1);
	else if (is_key_down(data->mlx, XK_Right))
		rotate(data, 1);
	if (!check_player_to_map_collision(data->map, data->map_size,
			(t_vec2){data->p_pos.x + (delta_hor.x + delta_vert.x),
			data->p_pos.y}))
		data->p_pos.x += (delta_hor.x + delta_vert.x);
	if (!check_player_to_map_collision(data->map, data->map_size,
			(t_vec2){data->p_pos.x, data->p_pos.y + (delta_hor.y
				+ delta_vert.y)}))
		data->p_pos.y += (delta_hor.y + delta_vert.y);
}
