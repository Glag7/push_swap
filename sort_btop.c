/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_btop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:02:27 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/10 18:06:47 by glaguyon         ###   ########.fr       */
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

	a->parts->prev->unum += b->dlst->num >= med && b->dlst->num < med2;
	a->parts->unum += b->dlst->num >= med2;
	rotate += b->dlst->num >= med && b->dlst->num < med2;
	while (b->dlst->num >= med2 && rotate)
		do_rotate(a, b, RA, &rotate);
	if (b->dlst->num >= med)
		op(a, b, PA);
	else if (rotate)
	{
		do_rotate(a, b, RR, &rotate);
		b->parts->prev->unum += 1;
	}
	else
	{
		op(a, b, RB);
		b->parts->prev->unum += 1;
	}
	while (!(a->parts->unum + b->parts->prev->unum
			+ a->parts->prev->unum < b->parts->unum) && rotate)
		do_rotate(a, b, RA, &rotate);
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
	ft_dlstadd_front(&(a->parts), tmp);
	tmp = ft_dlstnew(0);
	if (tmp == NULL)
		return (ERR_AINTNOWAY);
	ft_dlstadd_back(&(a->parts), tmp);
	med = get_median(b->dlst, b->parts->unum, 7 * b->parts->unum / 16, &err);
	if (!err)
		med2 = get_median(b->dlst, b->parts->unum,
				85 * b->parts->unum / 128, &err);
	while (!err && a->parts->unum + b->parts->prev->unum
		+ a->parts->prev->unum < b->parts->unum)
		part_stack_loop(a, b, med, med2);
	return (err);
}

static void	sort_btop_little(t_stack *a, t_stack *b, size_t size)
{
	char	badb;
	char	bada;

	badb = size > 2 && b->dlst->num > b->dlst->next->num
		&& b->dlst->next->next->num > b->dlst->num;
	bada = size > 2 && b->dlst->next->num > b->dlst->num
		&& b->dlst->next->next->num > b->dlst->next->num;
	if (badb)
		op(a, b, RB);
	op(a, b, PA);
	if (bada)
		op(a, b, RA);
	op(a, b, PA);
	if (a->dlst->num > a->dlst->next->num)
		op(a, b, SA);
	if (badb)
		op(a, b, RRB);
	if (size > 2)
		op(a, b, PA);
	if (a->dlst->num > a->dlst->next->num)
		op(a, b, SA);
	if (bada)
		op(a, b, RRA);
}

int	sort_btop(t_stack *a, t_stack *b)
{
	int	err;

	err = 0;
	if (b->parts->unum > 3)
	{
		priority(B_BOT);
		priority(A_BOT);
		priority(A_TOP);
		err = part_stack(a, b);
	}
	else if (b->parts->unum > 1)
		sort_btop_little(a, b, b->parts->unum);
	else if (b->parts->unum)
		op(a, b, PA);
	return (err);
}
