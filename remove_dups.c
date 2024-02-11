/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dups.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:36:33 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/05 23:35:20 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	remove_rarra(t_str buff)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	while (i++ < buff.len - 1)
	{
		n = 0;
		while (!(buff.s[i] & (RRA | SA | PA | PB)) && i < buff.len)
		{
			n += !!(buff.s[i] & RA);
			i++;
		}
		j = i;
		while (n && !(buff.s[j] & (SA | PA | PB)) && j < buff.len)
		{
			if (buff.s[j] & RRA)
			{
				n -= 1;
				erase_instr(buff.s + i, RA);
				buff.s[j] &= ~RRA;
			}
			j++;
		}
	}
}

static void	remove_rbrrb(t_str buff)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	while (i++ < buff.len - 1)
	{
		n = 0;
		while (!(buff.s[i] & (RRB | SB | PA | PB)) && i < buff.len)
		{
			n += !!(buff.s[i] & RB);
			i++;
		}
		j = i;
		while (n && !(buff.s[j] & (SB | PA | PB)) && j < buff.len)
		{
			if (buff.s[j] & RRB)
			{
				n -= 1;
				erase_instr(buff.s + i, RB);
				buff.s[j] &= ~RRB;
			}
			j++;
		}
	}
}

static void	remove_rrara(t_str buff)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	while (i++ < buff.len - 1)
	{
		n = 0;
		while (!(buff.s[i] & (RA | SA | PA | PB)) && i < buff.len)
		{
			n += !!(buff.s[i] & RRA);
			i++;
		}
		j = i;
		while (n && !(buff.s[j] & (SA | PA | PB)) && j < buff.len)
		{
			if (buff.s[j] & RA)
			{
				n -= 1;
				erase_instr(buff.s + i, RRA);
				buff.s[j] &= ~RA;
			}
			j++;
		}
	}
}

static void	remove_rrbrb(t_str buff)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	while (i++ < buff.len - 1)
	{
		n = 0;
		while (!(buff.s[i] & (RB | SB | PA | PB)) && i < buff.len)
		{
			n += !!(buff.s[i] & RRB);
			i++;
		}
		j = i;
		while (n && !(buff.s[j] & (SB | PA | PB)) && j < buff.len)
		{
			if (buff.s[j] & RB)
			{
				n -= 1;
				erase_instr(buff.s + i, RRB);
				buff.s[j] &= ~RB;
			}
			j++;
		}
	}
}

void	remove_dups(t_str buff)
{
	remove_rarra(buff);
	remove_rbrrb(buff);
	remove_rrara(buff);
	remove_rrbrb(buff);
	remove_dups2(buff);
}
