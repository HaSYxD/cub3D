#include <cub3d.h>

t_button	get_button(t_rec body)
{
	return ((t_button){
		.body = body,
		.state = 0
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
	}
	else
		if (button->state == -1)
			button->state = 0;
}

void	draw_button(t_button button, t_data *data)
{
	if (button.state == 1)
		square_to_fbuff(&data->frame_buffer, (t_vec2){button.body.x, button.body.y},
				(t_vec2){button.body.width, button.body.height}, MLX_WHITE);
	else if (button.state == -1)
		square_to_fbuff(&data->frame_buffer, (t_vec2){button.body.x, button.body.y},
				(t_vec2){button.body.width, button.body.height}, MLX_LGRAY);
	else
		square_to_fbuff(&data->frame_buffer, (t_vec2){button.body.x, button.body.y},
				(t_vec2){button.body.width, button.body.height}, MLX_DGRAY);
}
