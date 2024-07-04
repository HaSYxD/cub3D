/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afromont <afromont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:15:18 by afromont          #+#    #+#             */
/*   Updated: 2024/06/25 15:07:30 by afromont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_checkmap(char *file)
{
	int		i;
	size_t	j;

	i = -1;
	j = 0;
	while (file[++i])
	{
		if (file[i] == ' ' || file[i] == '1' || file[i] == '0' || file[i]
			== 'N' || file[i] == 'S' || file[i] == 'W' || file[i] == 'E')
			j++;
	}
	if (j == ft_strlen(file))
		return (1);
	return (0);
}

int	ft_splitfile(char **file, t_garb *gc, t_cdata *cdata)
{
	t_count	c;

	c = (t_count){-1, 0, 0};
	while (file[++c.i])
		c.k++;
	c.i -= 1;
	while (c.i > 0)
	{
		if (ft_checkmap(file[c.i]) == 0)
			break ;
		c.i--;
	}
	if (check_double(file, c.i) != 0)
		return (1);
	cdata->texture = allocate(sizeof(char *) * (c.k - c.i) + 1, gc);
	c.j = -1;
	c.k = 0;
	while (++c.j <= c.i)
		cdata->texture[c.j + c.k] = ft_strdup(file[c.j], gc);
	cdata->texture[c.j + c.k] = NULL;
	cdata->map = file + c.i + 1;
	return (0);
}

int	closemap(char *file)
{
	int	i;

	i = -1;
	while (file[++i])
		if (file[i] != '1' && file[i] != ' ')
			return (1);
	return (0);
}

int	ft_readfile(char **agv, t_garb *gc, t_cdata *cdata)
{
	t_count	c;
	char	*tmp;
	char	*line;
	char	**file;

	c = (t_count){0, -1, 0};
	line = "";
	tmp = "";
	c.k = open(agv[1], O_RDONLY);
	if (c.k == -1)
		return (printf("Error\nInvalid file\n"), 1);
	while (gnl(c.k, &tmp, gc) > 0)
	{
		line = ft_strjoin(line, tmp, gc);
		if (tmp[0] != '\n')
			c.i++;
	}
	if (line[0] == '\0')
		return (printf("Error\nInvalid file\n"), 1);
	file = ft_split(line, '\n', gc);
	if (closemap(file[c.i - 1]) != 0)
		return (printf("Error\nInvalid map\n"), 1);
	if (ft_splitfile(file, gc, cdata) != 0)
		return (printf("Error\nDouble map\n"), 1);
	return (ft_close(1, c.k), 0);
}

int	ft_cparsing(char **agv, t_garb *gc, t_cdata *cdata)
{
	int	i;
	int	fd;

	i = -1;
	if (ft_readfile(agv, gc, cdata) != 0)
		return (1);
	ft_initextures(cdata);
	if (ft_textures(gc, cdata) != 0)
		return (1);
	while (++i < 4)
	{
		fd = open(cdata->wall_tex[i], O_RDONLY);
		if (fd == -1)
			return (printf("Error\ntexture is invalide: %s\n",
					cdata->wall_tex[i]), 1);
		ft_close(1, fd);
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
