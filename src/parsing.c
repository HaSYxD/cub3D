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
	char *tmp[4];

	i = -1;
	//tmp = NULL;
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
		/*else if (ft_texturevalide(cdata->texture[i]) == 5)
			tmp[4] = ft_strdup(cdata->texture[i] + 2, gc);
		else if (ft_texturevalide(cdata->texture[i]) == 6)
			tmp[5] = ft_strdup(cdata->texture[i] + 2, gc);*/
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

void ft_readfile(char **agv, t_garb *gc, t_cdata *cdata)
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
	file = ft_split(line, '\n', gc);
	close(fd);
	ft_splitfile(file, gc, cdata);
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

void ft_map(t_garb *gc, t_cdata *cdata)
{
	size_t	colon;
	int		i;

	i = -1;
	colon = 0;
	(void) gc;
	while (cdata->map[++i])
	{
		if (ft_strlen(cdata->map[i]) > colon)
			colon = ft_strlen(cdata->map[i]);
	}
	cdata->map_size = (t_vec2){colon, i};
	printf("map size : %f %f\n", cdata->map_size.x, cdata->map_size.y);
}

int	ft_cparsing(char **agv, t_garb *gc, t_cdata *cdata)
{
	int	i;

	i = -1;
	ft_readfile(agv, gc, cdata);
	ft_initextures(cdata);
	if (ft_textures(gc, cdata) != 0)
		return (1);
	while (++i < 4)
	{
		if (open(cdata->wall_tex[i], O_RDONLY) == -1)
			return (printf("Error\nThis texture is invalide: %s\n", cdata->wall_tex[i]), 1);
	}
	ft_map(gc, cdata);
	return (0);
}

/*int	ft_eparsing(char **agv, t_garb *gc, t_edata *edata)
{
	char **file;

	file = ft_readfile(agv, gc);
	ft_textures(file, gc, edata);
}*/
