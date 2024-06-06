/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:55:44 by aliaudet          #+#    #+#             */
/*   Updated: 2024/04/01 15:03:30 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_splitstrs(const char *s, int start, int end, t_garb *gc)
{
	char	*dst;
	int		i;

	dst = allocate((end - start + 1) * sizeof(char), gc);
	if (!dst)
		return (NULL);
	i = 0;
	while (start < end)
		dst[i++] = s[start++];
	dst[i] = '\0';
	return (dst);
}

char	**ft_split(const char *s, char c, t_garb *gc)
{
	char	**split;
	size_t	i;
	size_t	j;
	int		index;

	split = allocate(sizeof(char *) * (ft_countw(s, c) + 1), gc);
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = get_splitstrs(s, index, i, gc);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
