/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_sorted.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:42:34 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/08 17:30:22 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static inline void	do_pa(t_stack *a, t_stack *b, size_t n)
{
	while (n)
	{
		op(a, b, PA);
		n--;
	}
	free(ft_dlstremove(&(b->parts), 0));
}

static inline void	do_rrb_pa(t_stack *a, t_stack *b, size_t n)
{
	while (n)
	{
		op(a, b, RRB);
		op(a, b, PA);
		n--;
	}
	free(ft_dlstremove(&(b->parts), -1));
}

static inline void	do_rra(t_stack *a, t_stack *b, size_t n)
{
	while (n)
	{
		op(a, b, RRA);
		n--;
	}
	free(ft_dlstremove(&(a->parts), -1));
}

char	push_sorted(t_stack *a, t_stack *b)
{
	char	part;

	part = priority(-1);
	if (part == A_TOP && a->parts->unum
		&& is_sorted(a->dlst, a->parts->unum, 0, 0))
		free(ft_dlstremove(&(a->parts), 0));
	else if (part == B_TOP && b->parts->unum
		&& is_sorted(b->dlst, b->parts->unum, 1, 0))
		do_pa(a, b, b->parts->unum);
	else if (part == A_BOT && a->parts->prev->unum
		&& is_sorted(a->dlst, a->parts->prev->unum, 1, 1))
		do_rra(a, b, a->parts->prev->unum);
	else if (part == B_BOT && b->parts->prev->unum
		&& is_sorted(b->dlst, b->parts->prev->unum, 1, 1))
		do_rrb_pa(a, b, b->parts->prev->unum);
	else
	{
		priority(part);
		return (0);
	}
	return (1);
}
