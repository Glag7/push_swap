/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_first_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:13:48 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/08 18:09:34 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_arr(ssize_t *arr)
{
	arr[0] = VERY_BIG;
	arr[1] = VERY_BIG;
	arr[2] = VERY_BIG;
}

static void	set_mins(t_stack *a, ssize_t *arr, size_t n)
{
	t_dlst	*curr;
	ssize_t	num;
	size_t	i;

	i = 0;
	curr = a->dlst;
	init_arr(arr);
	while (++i < n + 1)
	{
		num = curr->num;
		if (num < arr[0])
		{
			arr[2] = arr[1];
			arr[1] = arr[0];
			arr[0] = num;
		}
		else if (num < arr[1])
		{
			arr[2] = arr[1];
			arr[1] = num;
		}
		else if (num < arr[2])
			arr[2] = num;
		curr = curr->next;
	}
}

static void	insert_sorted(t_stack *a, t_stack *b, ssize_t *vals, size_t n)
{
	op(a, b, PB);
	if (b->dlst->num == vals[0])
	{
		while (b->dlst->prev->num > vals[0])
		{
			if (a->dlst->prev->num <= vals[n - 1])
				op(a, b, RRR);
			else
				op(a, b, RRB);
		}
		if (b->dlst->num < b->dlst->next->num
			&& a->dlst->num > a->dlst->next->num)
			op(a, b, SS);
		else if (b->dlst->num < b->dlst->next->num)
			op(a, b, SB);
	}
	if (b->dlst->num < b->dlst->next->num)
		op(a, b, SB);
	else if (a->dlst->num > vals[n - 1]
		&& a->dlst->prev->num > vals[n - 1]
		&& b->dlst->next->num > b->dlst->num)
		op(a, b, RR);
	else if (b->dlst->next->num > b->dlst->num)
		op(a, b, RB);
}

void	little_sort(t_stack *a, t_stack *b)
{
	t_dlst	*dlst;

	dlst = a->dlst;
	if (a->size == 3)
	{
		if (dlst->next->num < dlst->num)
			dlst = dlst->next;
		if (a->dlst->prev->num < dlst->num)
			dlst = a->dlst->prev;
		if (b->size && b->dlst->num < b->dlst->next->num
			&& dlst->next->num > dlst->prev->num)
			op(a, b, SS);
		else if (dlst->next->num > dlst->prev->num)
			op(a, b, SA);
		if (dlst == a->dlst->next)
			op(a, b, RA);
		else if (dlst == a->dlst->prev)
			op(a, b, RRA);
	}
	else if (b->size && (b->dlst->num < b->dlst->next->num)
		&& a->size == 2 && (dlst->num > dlst->next->num))
		op(a, b, SS);
	else if (a->size == 2 && (dlst->num > dlst->next->num))
		op(a, b, SA);
}

int	little_part(t_stack *a, t_stack *b)
{
	t_dlst	*tmp;
	ssize_t	val[3];
	size_t	n;

	if (a->size < 4 || is_sorted(a->dlst, a->size, 0, 0))
		return (0);
	n = 0;
	tmp = ft_dlstnew((void *)(a->size / 2));
	if (tmp != NULL)
		ft_dlstadd_front(&(b->parts), tmp);
	set_mins(a, val, a->size);
	while (tmp != NULL && a->size > n + 1)
	{
		if (a->dlst->num <= val[1 + (b->parts->num > 2)])
		{
			insert_sorted(a, b, val, 2 + (b->parts->num > 2));
			n++;
		}
		else if (a->dlst->prev->num <= val[1 + (b->parts->num > 2)])
			op(a, b, RRA);
		else
			op(a, b, RA);
	}
	priority(B_TOP);
	return (tmp == NULL);
}
