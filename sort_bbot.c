/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bbot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:40:57 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/10 18:01:42 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	part_stack_loop(t_stack *a, t_stack *b, ssize_t med, ssize_t med2)
{
	op(a, b, RRB);
	if (b->dlst->num < med)
	{
		op(a, b, PA);
		op(a, b, RA);
		a->parts->prev->unum += 1;
	}
	else if (b->dlst->num < med2)
		b->parts->unum += 1;
	else
	{
		op(a, b, PA);
		a->parts->unum += 1;
	}
}

static inline int	add_parts(t_stack *a, t_stack *b)
{
	t_dlst	*tmp;

	tmp = ft_dlstnew(0);
	if (tmp == NULL)
		return (ERR_AINTNOWAY);
	ft_dlstadd_front(&(b->parts), tmp);
	tmp = ft_dlstnew(0);
	if (tmp == NULL)
		return (ERR_AINTNOWAY);
	ft_dlstadd_back(&(a->parts), tmp);
	tmp = ft_dlstnew(0);
	if (tmp == NULL)
		return (ERR_AINTNOWAY);
	ft_dlstadd_front(&(a->parts), tmp);
	return (0);
}

static int	part_stack(t_stack *a, t_stack *b)
{
	t_dlst	*tmp;
	ssize_t	med;
	ssize_t	med2;
	size_t	i;
	int		err;

	if (add_parts(a, b))
		return (ERR_AINTNOWAY);
	tmp = b->dlst;
	i = 0;
	while (i < b->parts->prev->unum)
	{
		tmp = tmp->prev;
		i++;
	}
	med = get_median(tmp, b->parts->prev->unum, b->parts->prev->unum / 8, &err);
	if (!err)
		med2 = get_median(tmp, b->parts->prev->unum,
				193 * b->parts->prev->unum / 256, &err);
	while (!err && b->parts->unum + a->parts->prev->unum
		+ a->parts->unum < b->parts->prev->unum)
		part_stack_loop(a, b, med, med2);
	return (err);
}

static void	sort_bbot_little(t_stack *a, t_stack *b, size_t size)
{
	size_t	rotated;

	op(a, b, RRB);
	rotated = !(b->dlst->num > b->dlst->prev->num);
	if (b->dlst->num > b->dlst->prev->num)
		op(a, b, PA);
	op(a, b, RRB);
	rotated += !(size == 2 || b->dlst->num > b->dlst->prev->num);
	if (size == 2 || b->dlst->num > b->dlst->prev->num)
		op(a, b, PA);
	if ((size == 2 || b->dlst->num > b->dlst->prev->num) && rotated)
	{
		rotated--;
		op(a, b, PA);
	}
	if (size > 2)
	{
		op(a, b, RRB);
		op(a, b, PA);
	}
	if (a->dlst->num > a->dlst->next->num)
		op(a, b, SA);
	while (--rotated + 1)
		op(a, b, PA);
}

int	sort_bbot(t_stack *a, t_stack *b)
{
	int	err;

	err = 0;
	if (b->parts->prev->unum > 3)
	{
		err = part_stack(a, b);
		priority(A_BOT);
		priority(B_TOP);
		priority(A_TOP);
	}
	else if (b->parts->prev->unum > 1)
		sort_bbot_little(a, b, b->parts->prev->unum);
	else if (b->parts->prev->unum)
	{
		op(a, b, RRB);
		op(a, b, PA);
	}
	return (err);
}
