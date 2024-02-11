/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dups2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:11:33 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/05 23:35:48 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	remove_papb(t_str buff)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	while (i++ < buff.len - 1)
	{
		n = 0;
		while (!(buff.s[i] & (RR | RRR | SS | PB)) && i < buff.len)
		{
			n += !!(buff.s[i] & PA);
			i++;
		}
		j = i;
		while (n && !(buff.s[j] & (RR | RRR | SS | PA)) && j < buff.len)
		{
			if (buff.s[j] & PB)
			{
				n -= 1;
				erase_instr(buff.s + i, PA);
				buff.s[j] &= ~PB;
			}
			j++;
		}
	}
}

static void	remove_pbpa(t_str buff)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	while (i++ < buff.len - 1)
	{
		n = 0;
		while (!(buff.s[i] & (RR | RRR | SS | PA)) && i < buff.len)
		{
			n += !!(buff.s[i] & PB);
			i++;
		}
		j = i;
		while (n && !(buff.s[j] & (RR | RRR | SS | PB)) && j < buff.len)
		{
			if (buff.s[j] & PA)
			{
				n -= 1;
				erase_instr(buff.s + i, PB);
				buff.s[j] &= ~PA;
			}
			j++;
		}
	}
}

void	remove_dups2(t_str buff)
{
	remove_papb(buff);
	remove_pbpa(buff);
}
