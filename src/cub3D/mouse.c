/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:29:03 by aliaudet          #+#    #+#             */
/*   Updated: 2024/07/02 18:29:05 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	toggle_mouse(t_cdata *data)
{
	if (is_key_pressed(data->mlx, XK_m))
	{
		if (data->state == MOUSE_ENABLE)
		{
			data->state = MOUSE_DISABLE;
			mlx_mouse_show(data->mlx->mlx, data->mlx->win);
		}
		else if (data->state == MOUSE_DISABLE)
		{
			data->state = MOUSE_ENABLE;
			mlx_mouse_hide(data->mlx->mlx, data->mlx->win);
		}
	}
}

void	mouse_control(t_cdata *data)
{
	float	speed;

	toggle_mouse(data);
	if (data->state == MOUSE_ENABLE)
	{
		update_mouse_pos(data->mlx);
		if (data->mlx->mouse_position.x > (WIN_W / 2) + 2)
		{
			speed = (data->mlx->mouse_position.x - (WIN_W / 2)) * 0.2;
			data->p_angle += speed * data->mlx->frame_time;
			mlx_mouse_move(data->mlx->mlx, data->mlx->win,
				WIN_W / 2, WIN_H / 2);
		}
		else if (data->mlx->mouse_position.x < (WIN_W / 2) - 2)
		{
			speed = ((WIN_W / 2) - data->mlx->mouse_position.x) * 0.2;
			data->p_angle -= speed * data->mlx->frame_time;
			mlx_mouse_move(data->mlx->mlx, data->mlx->win,
				WIN_W / 2, WIN_H / 2);
		}
	}
}
