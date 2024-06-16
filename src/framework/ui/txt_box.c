/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_box.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:36:51 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/16 22:38:15 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub_framework.h>

t_txtbox	get_txtbox(t_rec body, char *title)
{
	return ((t_txtbox){
		.body = body,
		.title = title,
		.txt = {0}
	});
}

void	update_txtbox(t_txtbox *txtbox, t_mlxctx *mlx)
{
	int	i;

	i = 0;
	if (check_collision_point_rec(txtbox->body, mlx->mouse_position))
	{
		while (i < MAX_TXTBOX_LEN && txtbox->txt[i])
			i++;
		if (mlx->key_state[1] == 65288 && i > 0)
			txtbox->txt[--i] = 0;
		else if (mlx->key_state[1] != 65288)
			txtbox->txt[i] = mlx->key_state[1];
		mlx->key_state[1] = 0;
	}
}

void	draw_txtbox(t_txtbox txtbox, t_mlxctx *mlx)
{
	t_rec	border;

	border = (t_rec){txtbox.body.x - 5, txtbox.body.y - 5,
		txtbox.body.width + 10, txtbox.body.height + 10};
	square_to_fbuff(mlx, border, MLX_LGRAY);
	square_to_fbuff(mlx, txtbox.body, MLX_WHITE);
	mlx_string_put(mlx->mlx, mlx->win, txtbox.body.x, txtbox.body.y - 5,
		color_to_int(MLX_WHITE), txtbox.title);
	mlx_string_put(mlx->mlx, mlx->win, txtbox.body.x,
		txtbox.body.y + txtbox.body.height,
		color_to_int(MLX_BLACK), txtbox.txt);
}
