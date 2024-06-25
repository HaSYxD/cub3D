/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afromont <afromont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:19:47 by afromont          #+#    #+#             */
/*   Updated: 2024/06/25 11:55:31 by afromont         ###   ########.fr       */
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
	t_count	c;
	char	**tmp;

	tmp = ft_split(str, ',', gc);
	
	c = (t_count){ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2])};
	if (c.i >= 0 && c.i <= 255 && c.j >= 0
		&& c.j <= 255 && c.k >= 0 && c.k <= 255)
		cdata->map_col[i] = (t_color){254, c.i, c.j, c.k};
	else
		return (1);
	return (0);
}

int	ft_splittextures(char **tmp, t_garb *gc, t_cdata *cdata)
{
	int	i;
	int	j;

	i = -1;
	if(tmp[0] == NULL || tmp[1] == NULL || tmp[2] == NULL || tmp[3] == NULL
		|| tmp[4] == NULL || tmp[5] == NULL)
		return (printf("Error\nTexture invalide\n"), 1);
	while (++i < 4)
	{
		j = -1;
		if (cdata->wall_tex[i] != NULL)
			return (printf("Error\ntexture : %s is saved\n", tmp[i]), 1);
		while (tmp[i][++j])
		{
			if (tmp[i][j] == '.')
			{
				cdata->wall_tex[i] = ft_strdup(&tmp[i][j], gc);
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
		if (ft_countw(cdata->texture[c.i], ' ') != 2 || ft_texturevalide(cdata->texture[c.i]) == 0)
			return (printf("Error\nTexture invalide\n"), 1);
		c.j = -1;
		while (++c.j < 6)
		{
			if (ft_texturevalide(cdata->texture[c.i]) == c.j + 1)
			{
				if (c.j < 4)
					tmp[c.j] = ft_strdup(cdata->texture[c.i] + 3, gc);
				else if (c.j >= 4)
					tmp[c.j] = ft_strdup(cdata->texture[c.i] + 2, gc);
			}
		}
	}
	if (ft_splittextures(tmp, gc, cdata) != 0)
		return (1);
	printf("%s\n %s\n %s\n %s\n", cdata->wall_tex[0], cdata->wall_tex[1], cdata->wall_tex[2], cdata->wall_tex[3]);
	return (0);
}
