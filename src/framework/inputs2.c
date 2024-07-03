/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:38:21 by aliaudet          #+#    #+#             */
/*   Updated: 2024/07/02 18:38:23 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub_framework.h>

int	is_key_down(t_mlxctx *mlx, int key)
{
	if (key == XK_Shift_L || key == XK_Control_L
		|| key == XK_Right || key == XK_Left
		|| key == XK_Up || key == XK_Down)
	{
		if (mlx->key_state[0] == key)
			return (1);
	}
	else if (mlx->key_state[1] == key)
		return (1);
	else if (mlx->key_state[2] == key)
		return (1);
	return (0);
}

int	is_key_pressed(t_mlxctx *mlx, int key)
{
	if (key == XK_Shift_L || key == XK_Control_L
		|| key == XK_Right || key == XK_Left
		|| key == XK_Up || key == XK_Down)
	{
		if (mlx->key_state[0] == key)
		{
			mlx->key_state[0] = 0;
			return (1);
		}
	}
	else if (mlx->key_state[1] == key)
	{
		mlx->key_state[1] = 0;
		return (1);
	}
	else if (mlx->key_state[2] == key)
	{
		mlx->key_state[2] = 0;
		return (1);
	}
	return (0);
}

void	update_mouse_pos(t_mlxctx *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	mlx_mouse_get_pos(mlx->mlx, mlx->win, &x, &y);
	mlx->mouse_position = (t_vec2){x, y};
}
