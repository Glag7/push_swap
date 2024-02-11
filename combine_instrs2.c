/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_instrs2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:38:06 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/05 23:42:14 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	merge_sasb(t_str buff)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < buff.len)
	{
		while (buff.s[i] != SA && i < buff.len)
			i++;
		j = i;
		while (buff.s[i] == SA && j < buff.len
			&& (!(buff.s[j] & (SB | RRA | RA | PA | PB))
				|| buff.s[j] == SS))
			j++;
		if (buff.s[j] == SB)
		{
			buff.s[i] &= ~SA;
			buff.s[j] |= SA;
		}
		i++;
	}
}

static void	merge_sbsa(t_str buff)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < buff.len)
	{
		while (buff.s[i] != SB && i < buff.len)
			i++;
		j = i;
		while (buff.s[i] == SA && j < buff.len
			&& (!(buff.s[j] & (SA | RRB | RB | PB | PB))
				|| buff.s[j] == SS))
			j++;
		if (buff.s[j] == SA)
		{
			buff.s[i] &= ~SB;
			buff.s[j] |= SB;
		}
		i++;
	}
}

void	combine_instrs2(t_str buff)
{
	merge_sasb(buff);
	merge_sbsa(buff);
}
