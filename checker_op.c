/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:17:34 by glaguyon          #+#    #+#             */
/*   Updated: 2024/01/31 16:36:21 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	doop(t_stack *a, t_stack *b, unsigned char instr)
{
	if (a->size > 1 && instr & RA)
		a->dlst = a->dlst->next;
	if (b->size > 1 && instr & RB)
		b->dlst = b->dlst->next;
	if (a->size > 1 && instr & RRA)
		a->dlst = a->dlst->prev;
	if (b->size > 1 && instr & RRB)
		b->dlst = b->dlst->prev;
	if (a->size > 1 && instr & SA)
		ft_dlstswap(&(a->dlst));
	if (b->size > 1 && instr & SB)
		ft_dlstswap(&(b->dlst));
	if (b->size && instr & PA)
	{
		a->size += 1;
		b->size -= 1;
		ft_dlstadd_front(&(a->dlst), ft_dlstremove(&(b->dlst), 0));
	}
	if (a->size && instr & PB)
	{
		b->size += 1;
		a->size -= 1;
		ft_dlstadd_front(&(b->dlst), ft_dlstremove(&(a->dlst), 0));
	}
}

static unsigned char	tstr_to_instr(char *s, int *err)
{
	if (ft_strncmp(s, "ra\n", -1) == 0)
		return (RA);
	if (ft_strncmp(s, "rb\n", -1) == 0)
		return (RB);
	if (ft_strncmp(s, "rr\n", -1) == 0)
		return (RR);
	if (ft_strncmp(s, "rra\n", -1) == 0)
		return (RRA);
	if (ft_strncmp(s, "rrb\n", -1) == 0)
		return (RRB);
	if (ft_strncmp(s, "rrr\n", -1) == 0)
		return (RRR);
	if (ft_strncmp(s, "sa\n", -1) == 0)
		return (SA);
	if (ft_strncmp(s, "sb\n", -1) == 0)
		return (SB);
	if (ft_strncmp(s, "ss\n", -1) == 0)
		return (SS);
	if (ft_strncmp(s, "pa\n", -1) == 0)
		return (PA);
	if (ft_strncmp(s, "pb\n", -1) == 0)
		return (PB);
	ft_gnl_tstr(-1025, 0);
	*err = 1;
	return (0);
}

static unsigned char	get_next_instr(int *err)
{
	t_str			tstr;
	unsigned char	instr;

	tstr = ft_gnl_tstr(0, 4096);
	if (tstr.len == 0)
	{
		*err = tstr.s == NULL;
		free(tstr.s);
		tstr = ft_gnl_tstr(-1025, 0);
		return (0);
	}
	else if (tstr.s[tstr.len -1] != '\n' || tstr.len > 4)
	{
		*err = 1;
		free(tstr.s);
		tstr = ft_gnl_tstr(-1025, 0);
		return (0);
	}
	*err = 0;
	instr = tstr_to_instr(tstr.s, err);
	free(tstr.s);
	return (instr);
}

int	do_instr(t_stack *stack)
{
	t_stack			a;
	t_stack			b;
	int				err;
	unsigned char	instr;

	a = (t_stack){stack->dlst, NULL, stack->size};
	b = (t_stack){NULL, NULL, 0};
	instr = get_next_instr(&err);
	while (!err && instr)
	{
		doop(&a, &b, instr);
		instr = get_next_instr(&err);
	}
	if (err)
	{
		clean(&a, &b);
		return (err);
	}
	if (b.size == 0 && is_sorted(a.dlst, a.size, 0, 0))
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
	clean(&a, &b);
	return (0);
}
