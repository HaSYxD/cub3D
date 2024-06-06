/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:39:00 by aliaudet          #+#    #+#             */
/*   Updated: 2024/05/14 16:39:02 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdlib.h>
# include <stdio.h>

# ifndef C_DEFAULT
#  define C_DEFAULT	"\033[0m"
# endif
# ifndef C_RED
#  define C_RED		"\033[0;31m"
# endif
# ifndef C_GREEN
#  define C_GREEN	"\033[0;32m"
# endif
# ifndef C_YELLOW
#  define C_YELLOW	"\033[0;33m"
# endif
# ifndef C_CYAN
#  define C_CYAN	"\033[0;36m"
# endif

# ifndef DEBUG
#  define DEBUG	0
# endif

typedef struct s_ptr
{
	struct s_ptr	*next;
	void			*data;
}	t_ptr;

typedef struct s_garb
{
	t_ptr	*alloc_ptr;
	size_t	blocks_num;
}	t_garb;

t_ptr	*add_to_collector(void *data, t_ptr *alloc_ptr);

void	*allocate(size_t size, t_garb *collector);
void	clean_garbage(t_garb *collector);
void	deallocate(void *ptr, t_garb *collector);

#endif
