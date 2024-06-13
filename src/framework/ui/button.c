/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:43:44 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/13 11:43:45 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_button	get_button(t_rec body, char *title, int type)
{
	return ((t_button){
		.body = body,
		.state = 0,
		.title = title,
		.type = type
	});
}

void	update_button(t_button *button, int new_state, t_data *data)
{
	if (check_collision_point_rec(button->body, data->mouse_position))
	{
		if (button->state == 0)
			button->state = -1;
		if (data->mouse_state == 1)
			button->state = new_state;
		else if (button->state > 0 && button->type == PUSH)
			button->state = 0;
	}
	else
		if (button->state == -1)
			button->state = 0;

}

void	draw_button(t_button button, t_data *data)
{
	if (button.state == 1)
		square_to_fbuff(&data->frame_buffer, button.body, MLX_WHITE);
	else if (button.state == 2)
		square_to_fbuff(&data->frame_buffer, button.body, MLX_RED);
	else if (button.state == -1)
		square_to_fbuff(&data->frame_buffer, button.body, MLX_LGRAY);
	else
		square_to_fbuff(&data->frame_buffer, button.body, MLX_DGRAY);
	if (button.title[0])
		mlx_string_put(data->mlx, data->win, button.body.x, button.body.y + button.body.height, color_to_int(MLX_RED), button.title);
}