/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:33:55 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/08 17:57:24 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/hdr/libft.h"

# define WSPACE "\f\n\r\t\v "

# define VERY_BIG 0x20000000000000

# define BSIZE 4096

# define ERR_NONUM 1
# define ERR_NOINT 2
# define ERR_AINTNOWAY 3
# define ERR_DUP 4

# define A_TOP 1
# define A_BOT 2
# define B_TOP 3
# define B_BOT 4

# define SA 1
# define SB 2
# define SS 3
# define RA 4
# define RB 8
# define RR 12
# define RRA 16
# define RRB 32
# define RRR 48
# define PA 64
# define PB 128

typedef struct s_stack
{
	t_dlst	*dlst;
	t_dlst	*parts;
	size_t	size;
}	t_stack;

//sort
int		sort_stack(t_stack *stack);

//median
ssize_t	get_median(t_dlst *dlst, size_t len, size_t n, int *err);

//op
void	op(t_stack *a, t_stack *b, unsigned char instr);

//utils
char	is_sorted(t_dlst *dlst, size_t size, char rev, char doprev);
int		clean_error(t_stack *a, t_stack *b);
void	erase_instr(char *buff, unsigned char instr);

//priority
char	priority(char part);

//first_sort
int		first_sort(t_stack *a, t_stack *b);

//little_first_sort
int		little_part(t_stack *a, t_stack *b);
void	little_sort(t_stack *a, t_stack *b);

//push_sorted
char	push_sorted(t_stack *a, t_stack *b);

//sort_atop
int		sort_atop(t_stack *a, t_stack *b);

//sort_btop
int		sort_btop(t_stack *a, t_stack *b);

//sort_abot
int		sort_abot(t_stack *a, t_stack *b);

//sort_bbot
int		sort_bbot(t_stack *a, t_stack *b);

//print_buffer
void	print_buffer(t_str buff);

//remove_dups
void	remove_dups(t_str buff);
void	remove_dups2(t_str buff);

//combine_instrs
void	combine_instrs(t_str buff);
void	combine_instrs2(t_str buff);

#endif
