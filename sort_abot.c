/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_abot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:24:00 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/10 17:54:46 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	part_stack_loop(t_stack *a, t_stack *b, ssize_t med, ssize_t med2)
{
	op(a, b, RRA);
	if (a->dlst->num < med)
	{
		op(a, b, PB);
		if (b->dlst->num < med2)
		{
			b->parts->prev->unum += 1;
			op(a, b, RB);
		}
		else
			b->parts->unum += 1;
	}
	else
		a->parts->unum += 1;
}

static inline int	add_parts(t_stack *a, t_stack *b)
{
	t_dlst	*tmp;

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
	tmp = a->dlst;
	i = 0;
	while (i < a->parts->prev->unum)
	{
		i++;
		tmp = tmp->prev;
	}
	med = get_median(tmp, a->parts->prev->unum,
			a->parts->prev->unum / 2, &err);
	if (!err)
		med2 = get_median(tmp, a->parts->prev->unum,
				31 * a->parts->prev->unum / 256, &err);
	while (!err && b->parts->unum + b->parts->prev->unum
		+ a->parts->unum < a->parts->prev->unum)
		part_stack_loop(a, b, med, med2);
	return (err);
}

static void	sort_abot_little(t_stack *a, t_stack *b)
{
	char	pushed;

	pushed = 0;
	op(a, b, RRA);
	if (a->dlst->num < a->dlst->prev->num
		&& a->dlst->num < a->dlst->prev->prev->num)
	{
		op(a, b, PB);
		pushed++;
	}
	op(a, b, RRA);
	if (pushed == 0 && a->dlst->num < a->dlst->prev->num
		&& a->dlst->num < a->dlst->next->num)
	{
		op(a, b, PB);
		pushed++;
	}
	if (pushed == 0 && a->dlst->num > a->dlst->next->num)
		op(a, b, SA);
	op(a, b, RRA);
	if (a->dlst->num > a->dlst->next->num)
		op(a, b, SA);
	if (pushed)
		op(a, b, PA);
}

int	sort_abot(t_stack *a, t_stack *b)
{
	int	err;

	err = 0;
	if (a->parts->prev->unum > 3)
	{
		priority(B_BOT);
		priority(B_TOP);
		priority(A_TOP);
		err = part_stack(a, b);
	}
	else if (a->parts->prev->unum > 2)
		sort_abot_little(a, b);
	else if (a->parts->prev->unum)
	{
		op(a, b, RRA);
		if (a->parts->prev->unum > 1)
			op(a, b, RRA);
		if (a->parts->prev->unum > 1 && a->dlst->num > a->dlst->next->num)
			op(a, b, SA);
	}
	return (err);
}
