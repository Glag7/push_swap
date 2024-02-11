/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:56:45 by glaguyon          #+#    #+#             */
/*   Updated: 2023/12/28 16:04:30 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_delarr(void *restrict arr, void (del)(void *restrict))
{
	size_t				i;
	void	*restrict	tmp;
	void	**restrict	ptr;

	i = 0;
	ptr = arr;
	tmp = ptr[i];
	while (tmp)
	{
		del(tmp);
		i++;
		tmp = ptr[i];
	}
	free(ptr);
}
