#include <cub3d.h>

t_button	get_button(t_rec body, t_color on_color, t_color off_color)
{
	return ((t_button){
		.on_color = on_color,
		.off_color = off_color,
		.body = body,
		.state = 0
	});
}

void	update_button(t_button *button, int new_state, t_data *data)
{
	if (check_collision_point_rec(button->body, data->mouse_position) && data->mouse_state == 1)
		button->state = new_state;

}

void	draw_button(t_button button, t_data *data)
{
	if (button.state)
		square_to_fbuff(&data->frame_buffer, (t_vec2){button.body.x, button.body.y},
				(t_vec2){button.body.width, button.body.height}, button.on_color);
	else
		square_to_fbuff(&data->frame_buffer, (t_vec2){button.body.x, button.body.y},
				(t_vec2){button.body.width, button.body.height}, button.off_color);
}
