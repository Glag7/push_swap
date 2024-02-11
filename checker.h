/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:32:06 by glaguyon          #+#    #+#             */
/*   Updated: 2024/01/31 00:51:14 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "libft/hdr/libft.h"

# define WSPACE "\f\n\r\t\v "

# define ERR_NONUM 1
# define ERR_NOINT 2
# define ERR_AINTNOWAY 3
# define ERR_DUP 4

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

//op
int		do_instr(t_stack *a);

//utils
char	is_sorted(t_dlst *dlst, size_t size, char rev, char doprev);
void	clean(t_stack *a, t_stack *b);

#endif
