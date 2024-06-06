/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:38:43 by aliaudet          #+#    #+#             */
/*   Updated: 2024/05/14 16:38:44 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgc.h"

t_ptr	*add_to_collector(void *data, t_ptr *alloc_ptr)
{
	t_ptr	*new_ptr;

	new_ptr = malloc(sizeof(t_ptr));
	if (!new_ptr)
	{
		if (DEBUG)
			printf("[%sERROR%s]Failed to add pointer :\"%p\" to "
				"garbage collection\n", C_RED, C_DEFAULT, data);
		return (alloc_ptr);
	}
	new_ptr->next = alloc_ptr;
	new_ptr->data = data;
	if (DEBUG)
		printf("[%sINFO%s]Pointer \"%s%p%s\" previously"
			" allocated as been added to the garbage colletor\n",
			C_CYAN, C_DEFAULT, C_YELLOW, new_ptr->data, C_DEFAULT);
	return (new_ptr);
}

void	deallocate(void *ptr, t_garb *collector)
{
	t_ptr	*data_buff;
	t_ptr	*buff;

	buff = collector->alloc_ptr;
	while (collector->alloc_ptr)
	{
		if (ptr == collector->alloc_ptr->next->data)
		{
			if (DEBUG)
				printf("[%sINFO%s] Pointer \"%s%p%s\" \
					as been de-allocated at run-time\n",
					C_CYAN, C_DEFAULT, C_YELLOW, ptr, C_DEFAULT);
			data_buff = collector->alloc_ptr->next->next;
			free(collector->alloc_ptr->next->data);
			free(collector->alloc_ptr->next);
			collector->alloc_ptr->next = data_buff;
			collector->blocks_num--;
			break ;
		}
		collector->alloc_ptr = collector->alloc_ptr->next;
	}
	collector->alloc_ptr = buff;
}

void	*allocate(size_t size, t_garb *collector)
{
	void	*new;

	new = malloc(size);
	if (!new)
	{
		if (DEBUG)
			printf("[%sERROR%s]Failed To allocate block of size : %ld\n",
				C_RED, C_DEFAULT, size);
		return (NULL);
	}
	if (DEBUG)
		printf("[%sINFO%s]Block of size : %ld as been allcated "
			"succesfully\n", C_CYAN, C_DEFAULT, size);
	collector->alloc_ptr = add_to_collector(new, collector->alloc_ptr);
	if (!collector->alloc_ptr)
	{
		free(new);
		return (NULL);
	}
	collector->blocks_num++;
	return (new);
}

void	clean_garbage(t_garb *collector)
{
	t_ptr	*buff;

	if (!collector->alloc_ptr)
	{
		if (DEBUG)
			printf("[%sSUCCES%s] All data as been free'd succesfully\n",
				C_GREEN, C_DEFAULT);
		return ;
	}
	buff = collector->alloc_ptr->next;
	if (collector->alloc_ptr->data && collector->alloc_ptr)
	{
		if (DEBUG)
			printf("[%sINFO%s] Data at pointer \"%s%p%s\" as been free'd\n",
				C_CYAN, C_DEFAULT, C_YELLOW,
				collector->alloc_ptr->data, C_DEFAULT);
		free(collector->alloc_ptr->data);
		free(collector->alloc_ptr);
		collector->blocks_num--;
	}
	collector->alloc_ptr = buff;
	return (clean_garbage(collector));
}
