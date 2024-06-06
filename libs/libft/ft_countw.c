/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:00:57 by aliaudet          #+#    #+#             */
/*   Updated: 2024/04/01 15:03:43 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countw(const char *s, char c)
{
	int	i;
	int	count;
	int	trigger;

	i = 0;
	count = 0;
	trigger = 0;
	while (s[i])
	{
		if (s[i] != c && trigger == 0)
		{
			trigger = 1;
			count++;
		}
		else if (s[i] == c)
			trigger = 0;
		i++;
	}
	return (count);
}
