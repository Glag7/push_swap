/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:32:52 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/08 18:08:55 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	sort_part(t_stack *a, t_stack *b)
{
	char	tosort;
	int		res;

	tosort = priority(-1);
	if (tosort == B_TOP)
	{
		res = sort_btop(a, b);
		free(ft_dlstremove(&(b->parts), 0));
	}
	else if (tosort == B_BOT)
	{
		res = sort_bbot(a, b);
		free(ft_dlstremove(&(b->parts), -1));
	}
	else if (tosort == A_BOT)
	{
		res = sort_abot(a, b);
		free(ft_dlstremove(&(a->parts), -1));
	}
	else
	{
		res = sort_atop(a, b);
		free(ft_dlstremove(&(a->parts), 0));
	}
	return (res);
}

int	sort_stack(t_stack *stack)
{
	t_stack	b;
	t_stack	a;
	int		err;

	a = (t_stack){stack->dlst, NULL, stack->size};
	b = (t_stack){NULL, NULL, 0};
	a.parts = ft_dlstnew(0);
	err = a.parts == NULL;
	if (!err)
		err = first_sort(&a, &b);
	if (err)
		return (clean_error(&a, &b));
	while (!err && (a.parts != a.parts->prev || b.parts))
	{
		if (!push_sorted(&a, &b)
			&& (a.parts != a.parts->prev || b.parts))
			err = sort_part(&a, &b);
	}
	if (err)
		return (clean_error(&a, &b));
	free(a.parts);
	return (0);
}
