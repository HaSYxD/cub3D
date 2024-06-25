/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mappars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afromont <afromont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:17:27 by afromont          #+#    #+#             */
/*   Updated: 2024/06/25 15:33:36 by afromont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	normalizemap(t_cdata *cdata, t_garb *gc)
{
	int	i;

	i = -1;
	while (++i < (int)cdata->map_size.y)
	{
		if (ft_strlen(cdata->map[i]) < cdata->map_size.x)
			cdata->map[i] = extendmap(cdata->map[i], cdata->map_size.x, gc);
	}
}

void	takepositionplayer(t_cdata *dat, int i, int j)
{
	dat->p_pos = (t_vec2){j + 0.5, i + 0.5};
	dat->p_angle = 3 * (M_PI / 2);
	if (dat->map[i][j] == 'S')
		dat->p_angle = M_PI / 2;
	else if (dat->map[i][j] == 'E')
		dat->p_angle = 0;
	else if (dat->map[i][j] == 'W')
		dat->p_angle = M_PI;
}

int	outofmap(t_cdata *dat, int i, int j)
{
	if (i == 0 && (dat->map[i][j] != '1' && dat->map[i][j] != ' ' ))
		return (1);
	if (i == dat->map_size.y && (dat->map[i][j] != '1'
		|| dat->map[i][j] != ' '))
		return (1);
	if ((dat->map[i][j] == '0' || isplayer(dat->map[i][j]))
		&& outmap(dat->map[i][j + 1]))
		return (1);
	if ((dat->map[i][j] == '0' || isplayer(dat->map[i][j]))
		&& outmap(dat->map[i][j - 1]))
		return (1);
	if ((dat->map[i][j] == '0' || isplayer(dat->map[i][j]))
		&& outmap(dat->map[i + 1][j]))
		return (1);
	if ((dat->map[i][j] == '0' || isplayer(dat->map[i][j]))
		&& outmap(dat->map[i - 1][j]))
		return (1);
	return (0);
}

int	mapvalide(t_cdata *dat)
{
	t_count	c;

	c = (t_count){-1, -1, 0};
	while (dat->map[++c.i])
	{
		c.j = -1;
		while (dat->map[c.i][++c.j])
		{
			if (isplayer(dat->map[c.i][c.j]) && c.k == 0)
			{
				c.k = 1;
				takepositionplayer(dat, c.i, c.j);
				dat->map[c.i][c.j] = '0';
			}
			else if (isplayer(dat->map[c.i][c.j]) && c.k == 1)
				return (1);
			if (outofmap(dat, c.i, c.j) != 0)
				return (1);
		}
	}
	if (c.k == 0)
		return (1);
	return (0);
}

int	ft_map(t_garb *gc, t_cdata *cdata)
{
	size_t	colon;
	int		i;

	i = -1;
	colon = 0;
	while (cdata->map[++i])
		if (ft_strlen(cdata->map[i]) > colon)
			colon = ft_strlen(cdata->map[i]);
	cdata->map_size = (t_vec2){colon, i};
	normalizemap(cdata, gc);
	if (mapvalide(cdata) != 0)
		return (printf("Error\nInvalid map\n"), 1);
	return (0);
}
