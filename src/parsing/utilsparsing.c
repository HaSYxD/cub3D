/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsparsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afromont <afromont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:34:34 by afromont          #+#    #+#             */
/*   Updated: 2024/06/25 15:34:39 by afromont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

int	isplayer(const char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	outmap(const char c)
{
	if (c == ' ' || c == 0)
		return (1);
	return (0);
}
