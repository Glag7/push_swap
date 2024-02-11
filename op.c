/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 20:17:34 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/05 23:32:02 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	doop(t_stack *a, t_stack *b, unsigned char instr)
{
	if (instr & RA)
		a->dlst = a->dlst->next;
	if (instr & RB)
		b->dlst = b->dlst->next;
	if (instr & RRA)
		a->dlst = a->dlst->prev;
	if (instr & RRB)
		b->dlst = b->dlst->prev;
	if (instr & SA)
		ft_dlstswap(&(a->dlst));
	if (instr & SB)
		ft_dlstswap(&(b->dlst));
	if (instr & PA)
	{
		a->size += 1;
		b->size -= 1;
		ft_dlstadd_front(&(a->dlst), ft_dlstremove(&(b->dlst), 0));
	}
	if (instr & PB)
	{
		b->size += 1;
		a->size -= 1;
		ft_dlstadd_front(&(b->dlst), ft_dlstremove(&(a->dlst), 0));
	}
}

static int	resize_buffer(t_str *buff, size_t *newlen)
{
	char	*tmp;

	if (*newlen == 0)
		*newlen = BSIZE;
	else
		*newlen *= 2;
	tmp = malloc(*newlen);
	if (tmp == NULL)
	{
		free(buff->s);
		return (ERR_AINTNOWAY);
	}
	ft_memcpy(tmp, buff->s, buff->len);
	free(buff->s);
	buff->s = tmp;
	return (0);
}

void	op(t_stack *a, t_stack *b, unsigned char instr)
{
	static t_str	buff = {NULL, 0};
	static size_t	maxlen = 0;

	if (buff.len + 4 > maxlen && instr && resize_buffer(&buff, &maxlen))
	{
		clean_error(a, b);
		exit(ERR_AINTNOWAY);
	}
	doop(a, b, instr);
	if (buff.s)
	{
		buff.s[buff.len] = instr;
		buff.len += 1;
	}
	if (instr == 0)
	{
		buff.len -= !!buff.len;
		if (a == NULL && b == NULL && buff.s)
			print_buffer(buff);
		free(buff.s);
		buff = (t_str){NULL, 0};
		maxlen = 0;
	}
}
