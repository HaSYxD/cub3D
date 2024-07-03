/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afromont <afromont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:19:47 by afromont          #+#    #+#             */
/*   Updated: 2024/06/25 15:10:57 by afromont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_initextures(t_cdata *cdata)
{
	int	i;

	i = -1;
	while (++i < 4)
		cdata->wall_tex[i] = NULL;
	cdata->map_col[0] = (t_color){0};
	cdata->map_col[1] = (t_color){0};
}

int	ft_parsargb(char *str, t_cdata *cdata, int i, t_garb *gc)
{
	t_count			c;
	unsigned int	tmp[3];

	c.i = 0;
	(void)gc;
	while (*str)
	{
		if (c.i == 3)
			break ;
		if (*str == '-')
			return (1);
		if (ft_isdigit(*str))
			tmp[c.i++] = ft_ptoi(&str);
		str++;
	}
	if (tmp[0] <= 255 && tmp[1] <= 255 && tmp[2] <= 255)
		cdata->map_col[i] = (t_color){254, tmp[0], tmp[1], tmp[2]};
	else
		return (1);
	return (0);
}

int	ft_splittextures(char **tmp, t_garb *gc, t_cdata *cdata)
{
	t_count	c;

	c = (t_count){-1, -1, -1};
	if (tmp[0] == NULL || tmp[1] == NULL || tmp[2] == NULL || tmp[3] == NULL
		|| tmp[4] == NULL || tmp[5] == NULL)
		return (printf("Error\nTexture invalide(split)\n"), 1);
	while (++c.i < 4)
	{
		c.j = -1;
		if (cdata->wall_tex[c.i] != NULL)
			return (printf("Error\ntexture : %s is saved\n", tmp[c.i]), 1);
		while (tmp[c.i][++c.j])
		{
			if (tmp[c.i][c.j] == '.')
			{
				cdata->wall_tex[c.i] = ft_strdup(&tmp[c.i][c.j], gc);
				break ;
			}
		}
	}
	if (ft_parsargb(tmp[4], cdata, 1, gc) != 0)
		return (printf("Error\nInvalid color: %s\n", tmp[4]), 1);
	if (ft_parsargb(tmp[5], cdata, 0, gc) != 0)
		return (printf("Error\nInvalid color: %s\n", tmp[5]), 1);
	return (0);
}

int	ft_texturevalide(char *f)
{
	int	i;

	i = -1;
	while (f[++i])
	{
		if ((i == 0 && f[i] == 'N' && f[i + 1] == 'O')
			|| (f[i] == 'N' && f[i + 1] == 'O' && f[i - 1] == ' '))
			return (1);
		else if ((i == 0 && f[i] == 'W' && f[i + 1] == 'E')
			|| (f[i] == 'W' && f[i + 1] == 'E' && f[i - 1] == ' '))
			return (2);
		else if ((i == 0 && f[i] == 'S' && f[i + 1] == 'O')
			|| (f[i] == 'S' && f[i + 1] == 'O' && f[i - 1] == ' '))
			return (3);
		else if ((i == 0 && f[i] == 'E' && f[i + 1] == 'A')
			|| (f[i] == 'E' && f[i + 1] == 'A' && f[i - 1] == ' '))
			return (4);
		else if ((i == 0 && f[i] == 'F' && f[i + 1] == ' ')
			|| (f[i] == 'F' && f[i + 1] == ' ' && f[i - 1] == ' '))
			return (5);
		else if ((i == 0 && f[i] == 'C' && f[i + 1] == ' ')
			|| (f[i] == 'C' && f[i + 1] == ' ' && f[i - 1] == ' '))
			return (6);
	}
	return (0);
}

int	ft_textures(t_garb *gc, t_cdata *cdata)
{
	t_count	c;
	char	*tmp[6];

	c = (t_count){-1, -1, -1};
	while (++c.k < 6)
		tmp[c.k] = NULL;
	while (cdata->texture[++c.i])
	{
		if (ft_texturevalide(cdata->texture[c.i]) == 0)
			return (printf("Error\nTexture invalide\n"), 1);
		c.j = -1;
		while (++c.j < 6)
		{
			if (ft_texturevalide(cdata->texture[c.i]) == c.j + 1)
			{
				if (c.j < 4)
					tmp[c.j] = ft_strdup(cdata->texture[c.i] + 3, gc);
				else if (c.j >= 4)
					tmp[c.j] = ft_strdup(cdata->texture[c.i] + 1, gc);
			}
		}
	}
	if (ft_splittextures(tmp, gc, cdata) != 0)
		return (1);
	return (0);
}
