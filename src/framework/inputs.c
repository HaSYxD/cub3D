/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:35:14 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/16 22:35:16 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub_framework.h>

int	mouse_press(int mouse_code, int x, int y, t_mlxctx *mlx)
{
	(void)x;
	(void)y;
	if (mouse_code >= 1)
		mlx->mouse_state = mouse_code;
	return (0);
}

int	mouse_release(int mouse_code, int x, int y, t_mlxctx *mlx)
{
	(void)mouse_code;
	(void)x;
	(void)y;
	mlx->mouse_state = 0;
	return (0);
}

int	mouse_move(int mouse_code, int x, int y, t_mlxctx *mlx)
{
	(void)mouse_code;
	(void)x;
	(void)y;
	mlx->mouse_state = 0;
	return (0);
}

int	key_press(int key_code, t_mlxctx *mlx)
{
	if (key_code == XK_Shift_L || key_code == XK_Control_L)
		mlx->key_state[0] = key_code;
	else
		mlx->key_state[1] = key_code;
	if (mlx->key_state[0] == XK_Shift_L)
	{
		if (ft_isalpha(mlx->key_state[1]))
			mlx->key_state[1] -= 32;
		else if (mlx->key_state[1] == '-')
			mlx->key_state[1] = '_';
	}
	return (0);
}

int	key_release(int key_code, t_mlxctx *mlx)
{
	if (key_code == XK_Shift_L || key_code == XK_Control_L)
		mlx->key_state[0] = 0;
	else
		mlx->key_state[1] = 0;
	return (0);
}
