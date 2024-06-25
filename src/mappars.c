/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mappars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afromont <afromont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:17:27 by afromont          #+#    #+#             */
/*   Updated: 2024/06/24 17:16:08 by afromont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*extendmap(char *str, int len, t_garb *gc)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = allocate(sizeof(char) * len + 1, gc);
	while (str[++i])
		tmp[i] = str[i];
	while (i < len)
		tmp[i++] = ' ';
	tmp[i] = '\0';
	deallocate(str, gc);
	return (tmp);
}

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

int	mapvalide(t_cdata *dat)
{
	t_count	c;

	c = (t_count){-1, -1, 0};
	while (dat->map[++c.i])
	{
		c.j = -1;
		while (dat->map[c.i][++c.j])
		{
			if ((dat->map[c.i][c.j] == 'N' || dat->map[c.i][c.j] == 'S' || dat->map[c.i][c.j] == 'W' || dat->map[c.i][c.j] == 'E') && c.k == 0)
			{
				c.k = 1;
				dat->p_pos = (t_vec2){c.j + 0.5, c.i + 0.5};
				dat->p_angle = 3 * (M_PI / 2);
				if (dat->map[c.i][c.j] == 'S')
					dat->p_angle = M_PI / 2;
				else if (dat->map[c.i][c.j] == 'E')
					dat->p_angle = 0;
				else if (dat->map[c.i][c.j] == 'W')
					dat->p_angle = M_PI;
				dat->map[c.i][c.j] = '0';
			}
			else if ((dat->map[c.i][c.j] == 'N' || dat->map[c.i][c.j] == 'S' || dat->map[c.i][c.j] == 'W' || dat->map[c.i][c.j] == 'E') && c.k == 1)
				return (1);
			if (c.i == 0 && (dat->map[c.i][c.j] != '1' && dat->map[c.i][c.j] != ' ' ))
				return (1);
			if (c.i == dat->map_size.y && (dat->map[c.i][c.j] != '1' || dat->map[c.i][c.j] != ' '))
				return (1);
			if (dat->map[c.i][c.j] == '0' && dat->map[c.i][c.j + 1] == ' ')
				return (1);
			if (dat->map[c.i][c.j] == '0' && dat->map[c.i][c.j - 1] == ' ')
				return (1);
			if (dat->map[c.i][c.j] == '0' && dat->map[c.i + 1][c.j] == ' ')
				return (1);
			if (dat->map[c.i][c.j] == '0' && dat->map[c.i - 1][c.j] == ' ')
				return (1);
		}
	}
	return (0);
}

int	ft_map(t_garb *gc, t_cdata *cdata)
{
	size_t	colon;
	int		i;
	int		j;

	i = -1;
	j = -1;
	colon = 0;
	(void)gc;
	while (cdata->map[++i])
		if (ft_strlen(cdata->map[i]) > colon)
			colon = ft_strlen(cdata->map[i]);
	cdata->map_size = (t_vec2){colon, i};
	normalizemap(cdata, gc);
	if (mapvalide(cdata) != 0)
		return (printf("Error\nInvalid map\n"), 1);
	return (0);
}
