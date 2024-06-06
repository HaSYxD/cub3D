/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:31:31 by aliaudet          #+#    #+#             */
/*   Updated: 2023/11/20 16:12:48 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_gnlstrlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_gnlstrjoin(char *s1, char *s2, t_garb *gc)
{
	size_t	i;
	size_t	j;
	char	*dst;

	if (!s1)
	{
		s1 = allocate(1 * sizeof(char), gc);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	dst = allocate(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1), gc);
	if (!dst)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			dst[i] = s1[i];
	while (s2[j] != '\0')
		dst[i++] = s2[j++];
	dst[ft_gnlstrlen(s1) + ft_gnlstrlen(s2)] = '\0';
	return (dst);
}

char	*ft_gnlstrchr(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	if (c == '\0')
		return ((char *)&str[ft_gnlstrlen(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
