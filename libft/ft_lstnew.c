/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:43:47 by yfu               #+#    #+#             */
/*   Updated: 2021/09/26 17:50:41 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nw;

	nw = (t_list *)ft_malloc(1, sizeof(t_list));
	if (!nw)
	{
		ft_putstr_fd("ERROR_IN_FT_LSTNEW\n", 1);
		return (NULL);
	}
	nw->val = content;
	nw->next = NULL;
	return (nw);
}
