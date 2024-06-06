/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_domstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:55:11 by aliaudet          #+#    #+#             */
/*   Updated: 2024/05/22 13:55:12 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_aschar(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_isprint(str[i]) && str[i] != ' ' && str[i] != '\t')
			return (1);
	return (0);
}

char	*ft_domstr(char *str, size_t start, size_t end, t_garb *gc)
{
	char	*s1;
	char	*s2;

	s1 = ft_substr(str, 0, start, gc);
	s2 = ft_substr(str, end, ft_strlen(str), gc);
	if (!ft_aschar(s1))
		return (s2);
	if (!ft_aschar(s2))
		return (s1);
	return (ft_strjoin(s1, s2, gc));
}
