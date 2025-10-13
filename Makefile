CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -I 42_libft -I includes -g3
RM					=	rm -f
NAME				=	minishell
CHECKER				=	checker

LIBFT_FILE			=	42_libft/libft.a
LDFLAGS     		=	-L 42_libft -l ft
MAKE_LIB			=	make -C

LIST_SRC_DIR		=	list_operations
ENV_SRC_DIR			=	env
UTILS_SRC_DIR		=	utils
BUILTINS_SRC_DIR	=	builtins

LIST_SRC			=	$(LIST_SRC_DIR)/ft_envadd_back.c \
						$(LIST_SRC_DIR)/ft_envclear.c \
						$(LIST_SRC_DIR)/ft_envsize.c \
						$(LIST_SRC_DIR)/ft_envadd_front.c \
						$(LIST_SRC_DIR)/ft_envlast.c \
						$(LIST_SRC_DIR)/ft_envprint.c \
						$(LIST_SRC_DIR)/ft_envfind.c \
						$(LIST_SRC_DIR)/ft_envnew.c

BUILTINS_SRC		=	$(BUILTINS_SRC_DIR)/builtin_call.c \
						$(BUILTINS_SRC_DIR)/ft_echo.c \
						$(BUILTINS_SRC_DIR)/ft_env.c \
						$(BUILTINS_SRC_DIR)/ft_export.c \
						$(BUILTINS_SRC_DIR)/export_helper.c \
						$(BUILTINS_SRC_DIR)/ft_pwd.c

UTILS_SRC			=	$(UTILS_SRC_DIR)/print.c \
						$(UTILS_SRC_DIR)/free_split.c

ENV_SRC				=	$(ENV_SRC_DIR)/env_parse.c

MINISHELL_SRC		=	main.c $(ENV_SRC) $(UTILS_SRC) $(BUILTINS_SRC) \
						$(LIST_SRC)

VALGRIND =	valgrind --leak-check=full --show-leak-kinds=all  --suppressions=readline.supp

 
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

val: $(NAME) clean
	$(VALGRIND) ./$(NAME)
 
re:					fclean all
 
.PHONY:				all lib_clean lib_fclean clean fclean re
