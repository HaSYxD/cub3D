#include <cub3d.h>

int	mouse_press(int mouse_code, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (mouse_code >= 1)
		data->mouse_state = mouse_code;
	return (0);
}

int	mouse_release(int mouse_code, int x, int y, t_data *data)
{
	(void)mouse_code;
	(void)x;
	(void)y;
	data->mouse_state = 0;
	return (0);
}

int	key_press(int key_code, t_data *data)
{
	if (key_code == XK_Shift_L || key_code == XK_Control_L)
		data->key_state[0] = key_code;
	else
		data->key_state[1] = key_code;
	if (data->key_state[0] == XK_Shift_L )
	{
		if (ft_isalpha(data->key_state[1]))
			data->key_state[1] -= 32;
		else if (data->key_state[1] == '-')
			data->key_state[1] = '_';
	}
	return (0);
}

int	key_release(int key_code, t_data *data)
{
	if (key_code == XK_Shift_L || key_code == XK_Control_L)
		data->key_state[0] = 0;
	else
		data->key_state[1] = 0;
	return (0);
}
