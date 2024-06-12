#include <cub3d.h>

int	check_collision_point_rec(t_rec rec, t_vec2 point)
{
	if ((point.x >= rec.x && point.x < (rec.x + rec.width))
		&& (point.y >= rec.y && point.y < (rec.y + rec.height)))
		return (1);
	return (0);
}
