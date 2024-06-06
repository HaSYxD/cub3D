/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:57:02 by aliaudet          #+#    #+#             */
/*   Updated: 2024/05/14 16:41:45 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s, t_garb *gc)
{
	char	*dest;
	int		i;

	i = 0;
	while (s[i])
		i++;
	i += 1;
	dest = allocate(sizeof(char) * i, gc);
	i = 0;
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
