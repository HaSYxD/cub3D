#include <cub3d.h>

static int	check_incr(int n1, int n2)
{
	if (n1 > n2)
		return (-1);
	return (1);
}

static void	first_case(t_mlxctx *mlx, t_vec2 p1, t_vec2 p2, t_color color)
{
	int	e;
	int	i;
	int	dx;
	int	dy;

	i = 0;
	e = abs((int)p2.x - (int)p1.x);
	dx = e;
	dy = 2 * abs((int)p2.y - (int)p1.y);
	while (i <= dx)
	{
		pixel_to_fbuff(mlx, p1, color);
		i++;
		p1.x += check_incr(p1.x, p2.x);
		e -= dy;
		if (e < 0)
		{
			p1.y += check_incr(p1.y, p2.y);
			e += dx * 2;
		}
	}
}

static void	second_case(t_mlxctx *mlx, t_vec2 p1, t_vec2 p2, t_color color)
{
	int	e;
	int	i;
	int	dx;
	int	dy;

	i = 0;
	e = abs((int)p2.y - (int)p1.y);
	dx = 2 * abs((int)p2.x - (int)p1.x);
	dy = e;
	while (i <= dy)
	{
		pixel_to_fbuff(mlx, p1, color);
		i++;
		p1.y += check_incr(p1.y, p2.y);
		e -= dx;
		if (e < 0)
		{
			p1.x += check_incr(p1.x, p2.x);
			e += dy * 2;
		}
	}
}

void	line_to_fbuff(t_mlxctx *mlx, t_vec2 p1, t_vec2 p2, t_color color)
{
	if (abs((int)p2.x - (int)p1.x) > abs((int)p2.y - (int)p1.y))
		first_case(mlx, p1, p2, color);
	else if (abs((int)p2.x - (int)p1.x) <= abs((int)p2.y - (int)p1.y))
		second_case(mlx, p1, p2, color);
}
