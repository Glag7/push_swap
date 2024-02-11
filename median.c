/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   median.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:04:40 by glaguyon          #+#    #+#             */
/*   Updated: 2024/01/28 16:03:33 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*dlst_to_arr(t_dlst *dlst, size_t len)
{
	int		*arr;
	size_t	i;

	arr = malloc(len * sizeof(int));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		arr[i] = dlst->num;
		dlst = dlst->next;
		i++;
	}
	return (arr);
}

static size_t	part_arr(int *arr, size_t start, size_t end)
{
	size_t	i;
	size_t	j;
	int		piv;

	i = start;
	j = start;
	piv = arr[end];
	while (j < end)
	{
		if (arr[j] <= piv)
		{
			ft_swapint(arr + i, arr + j);
			i++;
		}
		j++;
	}
	ft_swapint(arr + i, arr + end);
	return (i);
}

static int	find_median(int *arr, size_t len, size_t n)
{
	size_t	tmp;
	size_t	i;
	size_t	j;

	tmp = (size_t)-1;
	i = 0;
	j = len - 1;
	while (tmp != n)
	{
		tmp = part_arr(arr, i, j);
		if (tmp < n)
			i = tmp + 1;
		else
			j = tmp - 1;
	}
	return (arr[n]);
}

ssize_t	get_median(t_dlst *dlst, size_t len, size_t n, int *err)
{
	int	*arr;
	int	med;

	arr = dlst_to_arr(dlst, len);
	if (arr == NULL)
	{
		*err = ERR_AINTNOWAY;
		return (0);
	}
	med = find_median(arr, len, n);
	free(arr);
	*err = 0;
	return (med);
}
