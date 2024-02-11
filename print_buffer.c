/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:05:07 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/08 17:02:39 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static inline void	print_instr(unsigned char instr)
{
	if (instr == SS)
		ft_putstr_fd("ss\n", 1);
	else if (instr == SA)
		ft_putstr_fd("sa\n", 1);
	else if (instr == SB)
		ft_putstr_fd("sb\n", 1);
	else if (instr == RR)
		ft_putstr_fd("rr\n", 1);
	else if (instr == RA)
		ft_putstr_fd("ra\n", 1);
	else if (instr == RB)
		ft_putstr_fd("rb\n", 1);
	else if (instr == RRR)
		ft_putstr_fd("rrr\n", 1);
	else if (instr == RRA)
		ft_putstr_fd("rra\n", 1);
	else if (instr == RRB)
		ft_putstr_fd("rrb\n", 1);
	else if (instr == PA)
		ft_putstr_fd("pa\n", 1);
	else if (instr == PB)
		ft_putstr_fd("pb\n", 1);
}

static size_t	instr_to_start(unsigned char instr)
{
	if (instr == SS)
		return (6);
	if (instr == SA)
		return (0);
	if (instr == SB)
		return (3);
	if (instr == RR)
		return (15);
	if (instr == RA)
		return (9);
	if (instr == RB)
		return (12);
	if (instr == RRR)
		return (26);
	if (instr == RRA)
		return (18);
	if (instr == RRB)
		return (22);
	if (instr == PA)
		return (30);
	if (instr == PB)
		return (33);
	return (0xFFFFFFFFFFFFFFF);
}

static inline void	add_instr(t_str *buff, unsigned char instr)
{
	static char	*instrs = "sa\nsb\nss\nra\nrb\nrr\nrra\nrrb\nrrr\npa\npb\n";
	size_t		len;
	size_t		start;

	if (instr == 0)
	{
		buff->s[buff->len] = 0;
		return ;
	}
	start = instr_to_start(instr);
	len = ft_in('\n', instrs + start) + 1;
	ft_memcpy(buff->s + buff->len, instrs + start, len);
	buff->len += len;
}

void	print_buffer(t_str buff)
{
	size_t	i;
	t_str	fbuff;

	i = 0;
	fbuff.len = 0;
	fbuff.s = malloc(buff.len * 5);
	remove_dups(buff);
	combine_instrs(buff);
	remove_dups(buff);
	while (!fbuff.s && i < buff.len)
	{
		print_instr(buff.s[i]);
		i++;
	}
	while (fbuff.s && i < buff.len)
	{
		add_instr(&fbuff, buff.s[i]);
		i++;
	}
	if (fbuff.s)
		write(1, fbuff.s, fbuff.len);
	free(fbuff.s);
}
