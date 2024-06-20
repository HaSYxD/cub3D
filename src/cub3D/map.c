#include <cub3d.h>

int	check_player_to_map_collision(char **map,t_vec2 msize, t_vec2 dpos)
{
	int	x;
	int	y;

	x = dpos.x;
	y = dpos.y;
	if (y >= msize.y || y < 0)
		return (1);
	if (x >= (int)ft_strlen(map[y]) || x < 0)
		return (1);
	if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == ' ')
		return (0);
	return (1);
}
