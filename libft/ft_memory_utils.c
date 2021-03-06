/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 00:04:33 by yfu               #+#    #+#             */
/*   Updated: 2021/05/17 01:48:42 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t elem_cnt, size_t elem_size)
{
	return (ft_memory(elem_cnt, elem_size, NULL, push_mem));
}

void	ft_free(void *del)
{
	ft_memory(0U, 0U, del, pop_mem);
}

void	ft_free_all(void)
{
	ft_memory(0U, 0U, NULL, clean_mem);
}
