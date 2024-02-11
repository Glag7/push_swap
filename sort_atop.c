/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_atop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:30:31 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/10 17:57:44 by glaguyon         ###   ########.fr       */
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

	b->parts->prev->unum += (a->dlst->num < med2);
	b->parts->unum += (a->dlst->num >= med);
	rotate += a->dlst->num < med2;
	while (rotate && a->dlst->num >= med)
		do_rotate(a, b, RB, &rotate);
	if (a->dlst->num < med2 || a->dlst->num >= med)
		op(a, b, PB);
	else if (rotate)
	{
		a->parts->prev->unum += 1;
		do_rotate(a, b, RR, &rotate);
	}
	else
	{
		a->parts->prev->unum += 1;
		op(a, b, RA);
	}
	while (!(b->parts->unum + b->parts->prev->unum
			+ a->parts->prev->unum < a->parts->unum) && rotate)
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
	tmp = ft_dlstnew(0);
	if (tmp == NULL)
		return (ERR_AINTNOWAY);
	ft_dlstadd_back(&(a->parts), tmp);
	med = get_median(a->dlst, a->parts->unum, a->parts->unum / 2, &err);
	if (!err)
		med2 = get_median(a->dlst, a->parts->unum,
				59 * a->parts->unum / 256, &err);
	while (!err && b->parts->unum + b->parts->prev->unum
		+ a->parts->prev->unum < a->parts->unum)
		part_stack_loop(a, b, med, med2);
	return (err);
}

static void	sort_atop_little(t_stack *a, t_stack *b)
{
	char	pushed;
	char	rotated;

	rotated = 0;
	if (a->dlst->next->num < a->dlst->num && a->dlst->next->num < a->dlst->num)
		op(a, b, SA);
	pushed = a->dlst->next->num > a->dlst->next->next->num;
	if (a->dlst->next->num > a->dlst->next->next->num)
		op(a, b, PB);
	if (a->dlst->num > a->dlst->next->num)
		op(a, b, SA);
	if (pushed && b->dlst->num > a->dlst->num
		&& b->dlst->num > a->dlst->next->num)
	{
		rotated = 1;
		op(a, b, RA);
	}
	if (pushed)
		op(a, b, PA);
	if (a->dlst->num > a->dlst->next->num)
		op(a, b, SA);
	if (rotated)
		op(a, b, RRA);
}

int	sort_atop(t_stack *a, t_stack *b)
{
	int	err;

	err = 0;
	if (a->parts->unum > 3)
	{
		err = part_stack(a, b);
		priority(B_BOT);
		priority(A_BOT);
		priority(B_TOP);
	}
	else if (a->parts->unum > 2)
		sort_atop_little(a, b);
	else if (a->parts->unum > 1 && a->dlst->num > a->dlst->next->num)
		op(a, b, SA);
	return (err);
}
