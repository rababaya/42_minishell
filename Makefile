CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -I 42_libft -I includes -g3
RM					=	rm -f
NAME				=	minishell
CHECKER				=	checker

LIBFT_FILE			=	42_libft/libft.a
LDFLAGS     		=	-L 42_libft -l ft
MAKE_LIB			=	make -C

# LIST_SRC_DIR		=	list_operations
# STACK_SRC_DIR		=	stack_operations
# BASIC_SORT_SRC_DIR	=	basic_sorts
# VALIDATION_SRC_DIR	=	validation

MINISHELL_SRC		=	main.c
# LIST_SRC			=	$(LIST_SRC_DIR)/ft_stackadd_back.c \
# 						$(LIST_SRC_DIR)/ft_stackclear.c \
# 						$(LIST_SRC_DIR)/ft_stacksize.c \
# 						$(LIST_SRC_DIR)/ft_stackadd_front.c \
# 						$(LIST_SRC_DIR)/ft_stacklast.c \
# 						$(LIST_SRC_DIR)/ft_stacknew.c

# STACK_SRC			=	$(STACK_SRC_DIR)/swap.c \
# 						$(STACK_SRC_DIR)/push.c \
# 						$(STACK_SRC_DIR)/rotate.c \
# 						$(STACK_SRC_DIR)/r_rotate.c

# BASIC_SORT_SRC		=	$(BASIC_SORT_SRC_DIR)/manual_sorting.c

# VALIDATION_SRC		=	$(VALIDATION_SRC_DIR)/join_split.c \
# 						$(VALIDATION_SRC_DIR)/validation.c
 
# PS_SRC				=	sorting/sorting.c \
# 						sorting/utils.c
 
# PUSH_SWAP_SRC		=	main.c \
# 						$(LIST_SRC) \
# 						$(STACK_SRC) \
# 						$(PS_SRC) \
# 						$(BASIC_SORT_SRC) \
# 						$(VALIDATION_SRC) 
 
MINISHELL_OBJ		=	$(MINISHELL_SRC:%.c=obj/minishell/%.o)

all:				$(NAME)

$(MINISHELL_OBJ):	obj/minishell/%.o: %.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@ 

$(LIBFT_FILE):
					$(MAKE_LIB) 42_libft
 
$(CHECKER):			$(LIBFT_FILE)
					$(CC) $(CFLAGS) $(LDFLAGS) -o $@

$(NAME):			$(MINISHELL_OBJ) $(LIBFT_FILE) 
					$(CC) $(CFLAGS) $(MINISHELL_OBJ) $(LDFLAGS) -lreadline -lncurses -o $@
 
lib_clean:
					$(MAKE_LIB) 42_libft clean
 
lib_fclean:
					$(MAKE_LIB) 42_libft fclean
 
clean:				lib_clean
					rm -rf obj
 
fclean:				clean lib_fclean
					$(RM) $(NAME) $(CHECKER)
 
re:					fclean all
 
.PHONY:				all lib_clean lib_fclean clean fclean re
