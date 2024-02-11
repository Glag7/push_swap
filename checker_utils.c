/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:48:00 by glaguyon          #+#    #+#             */
/*   Updated: 2024/01/31 01:27:30 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

char	is_sorted(t_dlst *dlst, size_t size, char rev, char doprev)
{
	ssize_t	value;
	ssize_t	prev;
	size_t	i;

	if (doprev)
		dlst = dlst->prev;
	prev = dlst->num;
	if (!doprev)
		dlst = dlst->next;
	else
		dlst = dlst->prev;
	i = 1;
	while (i < size)
	{
		value = dlst->num;
		if (value < prev != rev)
			return (0);
		prev = value;
		if (!doprev)
			dlst = dlst->next;
		else
			dlst = dlst->prev;
		i++;
	}
	return (1);
}

void	clean(t_stack *a, t_stack *b)
{
	if (a && a->size)
		ft_dlstclear(&(a->dlst), 0);
	if (b && b->size)
		ft_dlstclear(&(b->dlst), 0);
	if (a && a->parts)
		ft_dlstclear(&(a->parts), 0);
	if (b && b->parts)
		ft_dlstclear(&(b->parts), 0);
}
