NAME = push_swap

COMP = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
      median.c \
      op.c \
      remove_dups.c \
      remove_dups2.c \
      combine_instrs.c \
      combine_instrs2.c \
      print_buffer.c \
      priority.c \
      utils.c \
      first_sort.c \
      little_first_sort.c \
      sort.c \
      push_sorted.c \
      sort_atop.c \
      sort_btop.c \
      sort_abot.c \
      sort_bbot.c \

SRC_BONUS = checker_main.c \
	    checker_op.c \
	    checker_utils.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : libft.a $(NAME)

libft.a :
	@make -C libft/ dlst str print
	@mv libft/libft.a libft.a
	@make -C libft/ clean

libft_bonus.a :
	@make -C libft/ str tstr file print dlst
	@mv libft/libft.a libft_bonus.a
	@make -C libft/ clean

bonus : checker
	
checker : libft_bonus.a $(OBJ_BONUS)
	@$(COMP) $(CFLAGS) $^ libft_bonus.a -o checker

$(NAME) : $(OBJ)
	@$(COMP) $(CFLAGS) $^ libft.a -o $@

%.o : %.c
	@$(COMP) $(CFLAGS) -c $^ -o $@

clean :
	@rm -f $(OBJ) $(OBJ_BONUS)
	@rm -f libft.a
	@rm -f libft_bonus.a
	@make -C libft clean

fclean : clean
	@rm -f $(NAME)
	@rm -f checker

chokbar :
	@make -C libft/ chokbar

re : fclean all

.PHONY: all fclean clean re bonus chokbar
