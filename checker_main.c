/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:32:58 by glaguyon          #+#    #+#             */
/*   Updated: 2024/01/31 00:51:36 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	ft_atoi_err(char *str, int *dst)
{
	ssize_t	num;
	char	neg;

	num = 0;
	while (ft_in(*str, WSPACE) != -1)
		str++;
	neg = *str == '-';
	if (*str == '+' || *str == '-')
		str++;
	while (ft_in(*str, "0123456789") != -1 && num < 3000000000)
	{
		neg += 2;
		num = num * 10 + *str - '0';
		str++;
	}
	if (neg % 2)
		num *= -1;
	if (num > 2147483647 || num < -2147483648)
		return (ERR_NOINT);
	while (ft_in(*str, WSPACE) != -1)
		str++;
	if (*str || neg >> 1 == 0)
		return (ERR_NONUM);
	*dst = num;
	return (0);
}

static char	in_list(t_dlst *dlst, int n)
{
	t_dlst	*start;

	start = dlst->prev;
	while (dlst != start)
	{
		if (n == dlst->num)
			return (1);
		dlst = dlst->next;
	}
	if (n == dlst->num)
		return (1);
	return (0);
}

static int	add_int(t_dlst **dlst, char *str)
{
	int		n;
	int		res;
	t_dlst	*new;

	res = ft_atoi_err(str, &n);
	if (res)
		return (res);
	if (*dlst && in_list(*dlst, n))
		return (ERR_DUP);
	new = malloc(sizeof(t_dlst));
	if (new == NULL)
		return (ERR_AINTNOWAY);
	new->num = n;
	new->next = new;
	new->prev = new;
	ft_dlstadd_back(dlst, new);
	return (0);
}

static int	parse_nums(t_stack *stack, char **argv)
{
	char	*tmp;
	int		res;

	stack->size = 0;
	stack->dlst = NULL;
	tmp = *argv;
	if (tmp == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		return (ERR_NONUM);
	}
	while (tmp)
	{
		res = add_int(&(stack->dlst), tmp);
		if (res)
		{
			ft_putstr_fd("Error\n", 2);
			ft_dlstclear(&(stack->dlst), 0);
			return (res);
		}
		argv++;
		tmp = *argv;
		stack->size += 1;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	int		res;

	if (argc == 2)
	{
		argv = ft_split_set(argv[1], WSPACE);
		if (argv == NULL)
		{
			ft_putstr_fd("Error\n", 2);
			return (ERR_AINTNOWAY);
		}
		res = parse_nums(&stack_a, argv);
		ft_freearr(argv);
	}
	else if (argc > 2)
		res = parse_nums(&stack_a, argv + 1);
	if (argc >= 2 && res)
		return (res);
	if (argc >= 2 && do_instr(&stack_a))
	{
		ft_putstr_fd("Error\n", 2);
		return (ERR_AINTNOWAY);
	}
	return (0);
}
