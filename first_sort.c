/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:19:02 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/10 17:52:21 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static inline void	do_rotate(t_stack *a, t_stack *b,
		unsigned char instr, size_t *rotate)
{
	op(a, b, instr);
	*rotate -= 1;
}

static void	part_stack_loop(t_stack *a, t_stack *b, ssize_t med, ssize_t med2)
{
	static size_t	rotate = 0;

	if (a->dlst->num < med && a->dlst->num < med2)
	{
		op(a, b, PB);
		rotate += (b->parts->unum || b->parts->prev != b->parts->next);
		b->parts->prev->unum += 1;
	}
	else if (a->dlst->num < med)
	{
		while (rotate)
			do_rotate(a, b, RB, &rotate);
		op(a, b, PB);
		b->parts->unum += 1;
	}
	else if (rotate)
		do_rotate(a, b, RR, &rotate);
	else if (a->dlst->prev->num < med)
		op(a, b, RRA);
	else
		op(a, b, RA);
	while (!(b->parts->unum + b->parts->prev->unum + 1 < a->size) && rotate)
		do_rotate(a, b, RB, &rotate);
}

static int	part_stack(t_stack *a, t_stack *b)
{
	t_dlst	*tmp;
	ssize_t	med;
	ssize_t	med2;
	int		err;

	tmp = ft_dlstnew(0);
	if (tmp == NULL)
		return (ERR_AINTNOWAY);
	ft_dlstadd_back(&(b->parts), tmp);
	tmp = ft_dlstnew(0);
	if (tmp == NULL)
		return (ERR_AINTNOWAY);
	ft_dlstadd_front(&(b->parts), tmp);
	med = get_median(a->dlst, a->size, a->size / 2, &err);
	if (!err)
		med2 = get_median(a->dlst, a->size, a->size / 4, &err);
	priority(B_BOT);
	priority(B_TOP);
	while (!err && b->parts->unum + b->parts->prev->unum + 1 < a->size)
		part_stack_loop(a, b, med, med2);
	return (err);
}

int	first_sort(t_stack *a, t_stack *b)
{
	int	err;

	err = 0;
	while (!err && a->size > 6 && !is_sorted(a->dlst, a->size, 0, 0))
		err = part_stack(a, b);
	if (!err && a->size < 7)
	{
		err = little_part(a, b);
		little_sort(a, b);
	}
	return (err);
}
