/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_instrs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:10:51 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/07 19:44:36 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	merge_rarb(t_str buff)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < buff.len)
	{
		while (buff.s[i] != RA && i < buff.len)
			i++;
		j = i;
		while (buff.s[i] == RA && j < buff.len
			&& (!(buff.s[j] & (RB | RRA | SA | PA | PB))
				|| buff.s[j] == RR))
			j++;
		if (buff.s[j] == RB)
		{
			buff.s[i] &= ~RA;
			buff.s[j] |= RA;
		}
		i++;
	}
}

static void	merge_rbra(t_str buff)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < buff.len)
	{
		while (buff.s[i] != RB && i < buff.len)
			i++;
		j = i;
		while (buff.s[i] == RB && j < buff.len
			&& (!(buff.s[j] & (RA | RRB | SB | PA | PB))
				|| buff.s[j] == RR))
			j++;
		if (buff.s[j] == RA)
		{
			buff.s[i] &= ~RB;
			buff.s[j] |= RB;
		}
		i++;
	}
}

static void	merge_rrarrb(t_str buff)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < buff.len)
	{
		while (buff.s[i] != RRA && i < buff.len)
			i++;
		j = i;
		while (buff.s[i] == RRA && j < buff.len
			&& (!(buff.s[j] & (RRB | RA | SA | PA | PB))
				|| buff.s[j] == RRR))
			j++;
		if (buff.s[j] == RRB)
		{
			buff.s[i] &= ~RRA;
			buff.s[j] |= RRA;
		}
		i++;
	}
}

static void	merge_rrbrra(t_str buff)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < buff.len)
	{
		while (buff.s[i] != RRB && i < buff.len)
			i++;
		j = i;
		while (buff.s[i] == RRB && j < buff.len
			&& (!(buff.s[j] & (RRA | RB | SB | PA | PB))
				|| buff.s[j] == RRR))
			j++;
		if (buff.s[j] == RRA)
		{
			buff.s[i] &= ~RRB;
			buff.s[j] |= RRB;
		}
		i++;
	}
}

void	combine_instrs(t_str buff)
{
	merge_rarb(buff);
	merge_rbra(buff);
	merge_rrarrb(buff);
	merge_rrbrra(buff);
	combine_instrs2(buff);
}
