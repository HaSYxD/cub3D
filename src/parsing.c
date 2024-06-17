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

void ft_splittextures(char **tmp, t_garb *gc, t_cdata *cdata)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (tmp[i][++j])
		{
			if (tmp[i][j] == '.')
				cdata->wall_tex[i] = ft_strdup(&tmp[i][j], gc);
		}
	}
}

int ft_textures(char **file , t_garb *gc, t_cdata *cdata)
{
	int i;
	int j;
	char *tmp[4];

	i = -1;
	while (++i < 4 )
	{
		j = -1;
		if (ft_countw(file[i], ' ') != 2)
			return (printf("Error\nTexture invalide\n"), 1);
		while(file[i][++j])
		{
			if (file[i][j] == 'N' && file[i][j + 1] == 'O')
				tmp[0] = ft_strdup(file[i] + j + 3, gc);
			else if (file[i][j] == 'W' && file[i][j + 1] == 'E')
				tmp[1] = ft_strdup(file[i] + j + 3, gc);
			else if (file[i][j] == 'S' && file[i][j + 1] == 'O')
				tmp[2] = ft_strdup(file[i] + j + 3, gc);
			else if (file[i][j] == 'E' && file[i][j + 1] == 'A')
				tmp[3] = ft_strdup(file[i] + j + 3, gc);
		}
	}
	i = -1;
	ft_splittextures(tmp, gc, cdata);
	i = -1;
	while (++i < 4)
	{
		printf("%s\n", cdata->wall_tex[i]);
	}
	return (0);
}

char **ft_readfile(char **agv, t_garb *gc)
{
	int fd;
	char *tmp;
	char *line;
	char **file;

	file = NULL;
	line = "";
	tmp = "";
	fd = open(agv[1], O_RDONLY);
	if (fd == -1)
		printf("Error\nInvalid file\n");
	while (gnl(fd, &tmp, gc) > 0)
	{
		line = ft_strjoin(line, tmp, gc);
		
	}
	file = ft_split(line, '\n', gc);
	return (file);
}
int	ft_cparsing(char **agv, t_garb *gc, t_cdata *cdata)
{
	char **file;

	file = NULL;
	file = ft_readfile(agv, gc);
	if (ft_textures(file, gc, cdata) != 0)
		return (1);
	return (0);
}

/*int	ft_eparsing(char **agv, t_garb *gc, t_edata *edata)
{
	char **file;

	file = ft_readfile(agv, gc);
	ft_textures(file, gc, edata);
}*/