/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:02:41 by glaguyon          #+#    #+#             */
/*   Updated: 2024/01/30 19:37:34 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	priority(char part)
{
	static char	priority[4096];
	static char	*curr = priority;

	if (part >= 0)
	{
		*curr = part;
		curr++;
		return (part);
	}
	curr--;
	return (*curr);
}
