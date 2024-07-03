/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:43:16 by aliaudet          #+#    #+#             */
/*   Updated: 2024/07/02 18:43:34 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ptoi(char **str)
{
	int	neg_count;
	int	pos_count;
	int	res;

	neg_count = 0;
	pos_count = 0;
	res = 0;
	while (*(*str) == ' ' || *(*str) == '\t' || *(*str) == '\r'
		|| *(*str) == '\n' || *(*str) == '\v' || *(*str) == '\f')
		(*str)++;
	while (*(*str) == '-' || *(*str) == '+')
	{
		if (*(*str) == '-')
			neg_count++;
		if (*(*str) == '+')
			pos_count++;
		(*str)++;
	}
	while (*(*str) && *(*str) >= '0' && *(*str) <= '9')
		res = res * 10 + *(*str)++ - '0';
	if ((neg_count + pos_count) > 1)
		return (0);
	if (neg_count == 1)
		res = -res;
	return (res);
}
