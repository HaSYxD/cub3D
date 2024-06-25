/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afromont <afromont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:15:18 by afromont          #+#    #+#             */
/*   Updated: 2024/06/25 11:49:30 by afromont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <cub_editor.h>

int	ft_errorarg(char **agv, int ac)
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

void	ft_splitfile(char **file, t_garb *gc, t_cdata *cdata)
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
	cdata->texture = allocate(sizeof(char *) * (c.k - c.i) + 1, gc);
	c.j = -1;
	c.k = 0;
	while (++c.j <= c.i)
	{
		if (ft_countw(file[c.j], ' ') == 2)
			cdata->texture[c.j + c.k] = ft_strdup(file[c.j], gc);
		else
			c.k--;
	}
	cdata->texture[c.j + c.k] = NULL;
	cdata->map = file + c.i + 1;
}

int	ft_readfile(char **agv, t_garb *gc, t_cdata *cdata)
{
	int		fd;
	int		i;
	int		j;
	char	*tmp;
	char	*line;
	char	**file;

	i = 0;
	j = -1;
	file = NULL;
	line = "";
	tmp = "";
	fd = open(agv[1], O_RDONLY);
	if (fd == -1)
		return(printf("Error\nInvalid file\n"), 1);
	while (gnl(fd, &tmp, gc) > 0)
	{
		line = ft_strjoin(line, tmp, gc);
		if (tmp[0] != '\n')
			i++;
	}
	if (line[0] == '\0')
		return (printf("Error\nInvalid file\n"), 1);	
	file = ft_split(line, '\n', gc);
	while (file[i - 1][++j])
		if (file[i - 1][j] != '1' && file[i - 1][j] != ' ')
			return (printf("Error\nInvalid map\n"), 1);
	close(fd);
	ft_splitfile(file, gc, cdata);
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
			return (printf("Error\ntexture is invalide: %s\n",
					cdata->wall_tex[i]), 1);
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
