/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afromont <afromont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:15:18 by afromont          #+#    #+#             */
/*   Updated: 2024/06/21 16:24:49 by afromont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <cub_editor.h>

int ft_errorarg(char **agv, int ac)
{
	if (ac == 3)
	{
		if (ft_strncmp(agv[1], "EDITOR", 6) != 0
		|| (ft_strncmp(agv[2] + (ft_strlen(agv[2]) - 4), ".cub", 4) != 0
		&& (agv[2][0] < '0' && agv[2][0] > '9')))
			return (printf("Error\nInvalid argument\n"), 1);
	}
	else if (ac == 2)
	{
		if (ft_strncmp(agv[1] + (ft_strlen(agv[1]) - 4), ".cub", 4) != 0)
			return (printf("Error\nInvalid file extension\n"), 1);
	}
	return (0);

}

int	ft_parsargb(char *str, t_cdata *cdata, int i, t_garb *gc)
{
	t_count	c;
	char **tmp;

	tmp = ft_split(str, ',', gc);
	c = (t_count){ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2])};
	if (c.i >= 0 && c.i <= 255 && c.j >= 0 && c.j <= 255 && c.k >= 0 && c.k <= 255)
		cdata->map_col[i] = (t_color){255, c.i, c.j, c.k};
	else
		return (1);
	return (0);
}

int ft_splittextures(char **tmp, t_garb *gc, t_cdata *cdata)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		if (cdata->wall_tex[i] != NULL)
			return (printf("Error\nThe texture : %s is already saved\n", tmp[i]), 1);
		while (tmp[i][++j])
		{
			if (tmp[i][j] == '.')
			{
				cdata->wall_tex[i] = ft_strdup(&tmp[i][j], gc);
				break;
			}
		}
	}
	if (ft_parsargb(tmp[4], cdata, 1, gc) != 0)
		return (printf("Error\nInvalid color: %s\n", tmp[4]), 1);
	if (ft_parsargb(tmp[5], cdata, 0, gc) != 0)
		return (printf("Error\nInvalid color: %s\n", tmp[5]), 1);
	return (0);
}

int ft_texturevalide(char *file)
{
	int i;

	i = -1;
	while (file[++i])
	{
		if ((i == 0 && file[i] == 'N' && file[i + 1] == 'O') || (file[i] == 'N' && file[i + 1] == 'O' && file[i - 1] == ' '))
			return (1);
		else if ((i == 0 && file[i] == 'W' && file[i + 1] == 'E') || (file[i] == 'W' && file[i + 1] == 'E' && file[i - 1] == ' '))
			return (2);
		else if ((i == 0 && file[i] == 'S' && file[i + 1] == 'O') || (file[i] == 'S' && file[i + 1] == 'O' && file[i - 1] == ' '))
			return (3);
		else if ((i == 0 && file[i] == 'E' && file[i + 1] == 'A') || (file[i] == 'E' && file[i + 1] == 'A' && file[i - 1] == ' '))
			return (4);
		else if ((i == 0 && file[i] == 'F' && file[i + 1] == ' ') || (file[i] == 'F' && file[i + 1] == ' ' && file[i - 1] == ' '))
			return (5);
		else if ((i == 0 && file[i] == 'C' && file[i + 1] == ' ') || (file[i] == 'C' && file[i + 1] == ' ' && file[i - 1] == ' '))
			return (6);

	}
	return (0);
}

int ft_textures(t_garb *gc, t_cdata *cdata)
{
	int i;
	char *tmp[6];

	i = -1;
	while (cdata->texture[++i])
	{
		if (ft_countw(cdata->texture[i], ' ') != 2)
			return (printf("Error\nTexture invalide\n"), 1);
		if (ft_texturevalide(cdata->texture[i]) == 0)
			return (printf("Error\nTexture invalide"), 1);
		else if (ft_texturevalide(cdata->texture[i]) == 1)
			tmp[0] = ft_strdup(cdata->texture[i] + 3, gc);
		else if (ft_texturevalide(cdata->texture[i]) == 2)
			tmp[1] = ft_strdup(cdata->texture[i] + 3, gc);
		else if (ft_texturevalide(cdata->texture[i]) == 3)
			tmp[2] = ft_strdup(cdata->texture[i] + 3, gc);
		else if (ft_texturevalide(cdata->texture[i]) == 4)
			tmp[3] = ft_strdup(cdata->texture[i] + 3, gc);
		else if (ft_texturevalide(cdata->texture[i]) == 5)
			tmp[4] = ft_strdup(cdata->texture[i] + 2, gc);
		else if (ft_texturevalide(cdata->texture[i]) == 6)
			tmp[5] = ft_strdup(cdata->texture[i] + 2, gc);
	}
	if (ft_splittextures(tmp, gc, cdata) != 0)
		return (1);
	return (0);
}

int ft_checkmap(char *file)
{
	int i;
	size_t j;

	i = -1;
	j = 0;
	while (file[++i])
	{
		if (file[i] == ' ' || file[i] == '1' || file[i] == '0' || file[i] == 'N'
		|| file[i] == 'S' || file[i] == 'W' || file[i] == 'E')
			j++;
	}
	if (j == ft_strlen(file))
		return (1);
	return (0);
}

char **normalizemap(t_cdata *cdata, t_garb *gc)
{
	t_count c;
	int len;
	char **map;

	c = (t_count){-1, -1, -1};
	map = allocate(sizeof(char *) * cdata->map_size.y + 1, gc);
	while (++c.i < (int)cdata->map_size.y)
	{
		len = ft_strlen(cdata->map[c.i]);
		map[c.i] = allocate(sizeof(char) * cdata->map_size.x + 1, gc);
		c.j = -1;
		while (++c.j < (int)cdata->map_size.x)
		{
			if (c.j < len)
				map[c.i][c.j] = cdata->map[c.i][c.j];
			else
				map[c.i][c.j] = ' ';
		}
		map[c.i][c.j] = '\0';
	}
	map[c.i] = NULL;
	return (map);
}

void ft_splitfile(char **file, t_garb *gc, t_cdata *cdata)
{
	size_t i;
	size_t j;
	int k;

	i = -1;
	j = 0;
	k = 0;
	while(file[++i])
		k++;
	i -= 1;
	while(i > 0)
	{
		if (ft_checkmap(file[i]) == 0)
			break;
		i--;
	}
	cdata->texture = allocate(sizeof(char *) * (k - i) + 1, gc);
	j = -1;
	k = 0;
	while (++j <= i)
	{
		if (ft_countw(file[j], ' ') != 0)
			cdata->texture[j + k] = ft_strdup(file[j], gc);
		else
			k--;
	}
	cdata->texture[j + k] = NULL;
	cdata->map = file + i + 1;
}

int ft_readfile(char **agv, t_garb *gc, t_cdata *cdata)
{
	int fd;
	int i;
	char *tmp;
	char *line;
	char **file;

	i = 0;
	file = NULL;
	line = "";
	tmp = "";
	fd = open(agv[1], O_RDONLY);
	if (fd == -1)
		printf("Error\nInvalid file\n");
	while (gnl(fd, &tmp, gc) > 0)
	{
		line = ft_strjoin(line, tmp, gc);
		i++;
	}
	if (line[0] == '\0')
			return (printf("Error\nInvalid file\n"), 1);
	file = ft_split(line, '\n', gc);
	close(fd);
	ft_splitfile(file, gc, cdata);
	return (0);
}

void ft_initextures(t_cdata *cdata)
{
	int i;

	i = -1;
	while (++i < 4)
		cdata->wall_tex[i] = NULL;
	cdata->map_col[0] = (t_color){0};
	cdata->map_col[1] = (t_color){0};
}

int mapvalide(t_cdata *dat)
{
	int i;
	int	j;
	int player;

	j = -1;
	i = -1;
	player = 0;
	while (dat->map[++i])
	{
		j = -1;
		while (dat->map[i][++j])
		{
			if ((dat->map[i][j] == 'N' || dat->map[i][j] == 'S' || dat->map[i][j] == 'W' || dat->map[i][j] == 'E') && player == 0)
			{
				player = 1;
				dat->map[i][j] = '0';
				dat->p_pos = (t_vec2){j + 0.5, i + 0.5};
				dat->p_angle = (dat->map[i][j] == 'N') ? -(M_PI / 2) : (dat->map[i][j] == 'S') ? (M_PI / 2) : (dat->map[i][j] == 'W') ? M_PI : 0;
			}
			else if ((dat->map[i][j] == 'N' || dat->map[i][j] == 'S' || dat->map[i][j] == 'W' || dat->map[i][j] == 'E') && player == 1)
				return (1);
			if (i == 0 && (dat->map[i][j] != '1' && dat->map[i][j] != ' ' ))
				return (1);
			if (i == dat->map_size.y && (dat->map[i][j] != '1' || dat->map[i][j] != ' '))
				return (1);
			if (dat->map[i][j] == '0' && dat->map[i][j + 1] == ' ')
				return (1);
			if (dat->map[i][j] == '0' && dat->map[i][j - 1] == ' ')
				return (1);
			if (dat->map[i][j] == '0' && dat->map[i + 1][j] == ' ')
				return (1);
			if (dat->map[i][j] == '0' && dat->map[i - 1][j] == ' ')
				return (1);
		}
	}
	return (0);
}

int ft_map(t_garb *gc, t_cdata *cdata)
{
	size_t	colon;
	int		i;

	i = -1;
	colon = 0;
	while (cdata->map[++i])
	{
		if (ft_strlen(cdata->map[i]) > colon)
			colon = ft_strlen(cdata->map[i]);
	}
	cdata->map_size = (t_vec2){colon, i};
	cdata->map = normalizemap(cdata, gc);
	if (mapvalide(cdata) != 0)
		return (printf("Error\nInvalid map\n"), 1);
	return (0);
}

int	ft_cparsing(char **agv, t_garb *gc, t_cdata *cdata)
{
	int	i;

	i = -1;
	if (ft_readfile(agv, gc, cdata) != 0)
		return (1);
	ft_initextures(cdata);
	if (ft_textures(gc, cdata) != 0)
		return (1);
	while (++i < 4)
	{
		if (open(cdata->wall_tex[i], O_RDONLY) == -1)
			return (printf("Error\nThis texture is invalide: %s\n", cdata->wall_tex[i]), 1);
	}
	if (ft_map(gc, cdata) != 0)
		return (1);
	return (0);
}

/*int	ft_eparsing(char **agv, t_garb *gc, t_edata *edata)
{
	char **file;

	file = ft_readfile(agv, gc);
	ft_textures(file, gc, edata);
}*/
