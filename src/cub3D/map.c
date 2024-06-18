#include <cub3d.h>

int	check_player_to_map_collision(char **map,t_vec2 msize, t_vec2 dpos)
{
	t_count	c;

	c = (t_count){-1, -1, 0};
	while (++c.j < msize.y)
	{
		while (++c.i < msize.x)
		{
			if (map[c.j][c.i] == '0' || map[c.j][c.i] == 'N' || map[c.j][c.i] == ' ')
				continue ;
			if (check_collision_point_rec((t_rec){c.i, c.j, 1, 1}, dpos))
				return (1);
		}
		c.i = -1;
	}
	return (0);
}
