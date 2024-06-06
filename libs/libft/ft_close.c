/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:20:50 by aliaudet          #+#    #+#             */
/*   Updated: 2024/05/16 17:20:56 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_close(int n_args, ...)
{
	va_list	args;
	int		fd;
	int		i;

	i = -1;
	va_start(args, n_args);
	while (++i < n_args)
	{
		fd = va_arg(args, int);
		if (fd > 0)
			close(fd);
	}
}
