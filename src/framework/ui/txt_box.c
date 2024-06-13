#include <cub3d.h>

t_txtbox	get_txtbox(t_rec body, char *title)
{
	return ((t_txtbox){
		.body = body,
		.title = title,
		.txt = {0}
	});
}

void	update_txtbox(t_txtbox *txtbox, t_data *data)
{
	int	i;

	i = 0;
	if (check_collision_point_rec(txtbox->body, data->mouse_position))
	{
		while (i < MAX_TXTBOX_LEN && txtbox->txt[i])
			i++;
		if (data->key_state[1] == 65288 && i > 0)
			txtbox->txt[--i] = 0;
		else if (data->key_state[1] != 65288)
			txtbox->txt[i] = data->key_state[1];
		data->key_state[1] = 0;
	}
}

void	draw_txtbox(t_txtbox txtbox, t_data *data)
{
	t_rec	border;

	border = (t_rec){txtbox.body.x-5, txtbox.body.y-5, txtbox.body.width+10, txtbox.body.height+10};
	square_to_fbuff(&data->frame_buffer, border, MLX_LGRAY);
	square_to_fbuff(&data->frame_buffer, txtbox.body, MLX_WHITE);
	mlx_string_put(data->mlx, data->win, txtbox.body.x, txtbox.body.y - 5, color_to_int(MLX_WHITE), txtbox.title);
	mlx_string_put(data->mlx, data->win, txtbox.body.x, txtbox.body.y + txtbox.body.height, color_to_int(MLX_BLACK), txtbox.txt);
}
