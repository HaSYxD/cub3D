/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:38:00 by aliaudet          #+#    #+#             */
/*   Updated: 2023/11/20 16:04:17 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*clean_stash(char *stash, t_garb *gc)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (NULL);
	dst = allocate(sizeof(char) * (ft_gnlstrlen(stash) - i + 1), gc);
	if (!dst)
		return (NULL);
	i++;
	while (stash[i])
		dst[j++] = stash[i++];
	dst[j] = '\0';
	return (dst);
}

char	*extract_line(char *stash, t_garb *gc)
{
	char	*dst;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	dst = allocate(sizeof(char) * (i + 2), gc);
	if (!dst)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		dst[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		dst[i] = '\0';
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*read_to_stash(int fd, char *stash, t_garb *gc)
{
	char	*buff;
	int		rd_bytes;

	buff = allocate(sizeof(char) * (GNL_BUFFER_SIZE + 1), gc);
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_gnlstrchr(stash, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, GNL_BUFFER_SIZE);
		if (rd_bytes == -1)
			return (NULL);
		buff[rd_bytes] = '\0';
		stash = ft_gnlstrjoin(stash, buff, gc);
	}
	return (stash);
}

char	*gnl(int fd, t_garb *gc)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || GNL_BUFFER_SIZE <= 0)
		return (0);
	stash = read_to_stash(fd, stash, gc);
	if (!stash)
		return (NULL);
	line = extract_line(stash, gc);
	stash = clean_stash(stash, gc);
	return (line);
}
