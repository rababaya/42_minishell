CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -I 42_libft -I includes -g3
RM					=	rm -f
NAME				=	minishell

LIBFT_FILE			=	42_libft/libft.a
LDFLAGS     		=	-L 42_libft -lft
MAKE_LIB			=	make -C

TKN_SRC_DIR			=	tkn_operations
ENV_OP_SRC_DIR		=	env_operations
ENV_SRC_DIR			=	env
UTILS_SRC_DIR		=	utils
BUILTINS_SRC_DIR	=	builtins
TKNSE_SRC_DIR		=	tokenisation
EXEC_SRC_DIR		=	execution
EXPND_SRC_DIR		=	expansion
SIGNALS_SRC_DIR		=	signals

ENV_OP_SRC			=	$(ENV_OP_SRC_DIR)/ft_envadd_back.c \
						$(ENV_OP_SRC_DIR)/ft_envclear.c \
						$(ENV_OP_SRC_DIR)/ft_envsize.c \
						$(ENV_OP_SRC_DIR)/ft_envadd_front.c \
						$(ENV_OP_SRC_DIR)/ft_envlast.c \
						$(ENV_OP_SRC_DIR)/ft_envprint.c \
						$(ENV_OP_SRC_DIR)/ft_envdelone.c \
						$(ENV_OP_SRC_DIR)/ft_envfind.c \
						$(ENV_OP_SRC_DIR)/ft_envnew.c

TKN_SRC				=	$(TKN_SRC_DIR)/ft_tknadd_back.c \
						$(TKN_SRC_DIR)/ft_tknadd_front.c \
						$(TKN_SRC_DIR)/ft_tknclear.c \
						$(TKN_SRC_DIR)/ft_tknsize.c \
						$(TKN_SRC_DIR)/ft_tknlast.c \
						$(TKN_SRC_DIR)/ft_tknprint.c \
						$(TKN_SRC_DIR)/ft_tknnew.c 

BUILTINS_SRC		=	$(BUILTINS_SRC_DIR)/builtin_call.c \
						$(BUILTINS_SRC_DIR)/ft_echo.c \
						$(BUILTINS_SRC_DIR)/ft_env.c \
						$(BUILTINS_SRC_DIR)/ft_cd.c \
						$(BUILTINS_SRC_DIR)/ft_export.c \
						$(BUILTINS_SRC_DIR)/ft_unset.c \
						$(BUILTINS_SRC_DIR)/ft_exit.c \
						$(BUILTINS_SRC_DIR)/export_helper.c \
						$(BUILTINS_SRC_DIR)/ft_pwd.c

UTILS_SRC			=	$(UTILS_SRC_DIR)/print.c \
						$(UTILS_SRC_DIR)/free_split.c \
						$(UTILS_SRC_DIR)/free_data.c \
						$(UTILS_SRC_DIR)/ft_strglue.c \
						$(UTILS_SRC_DIR)/ft_iswhitespace.c

ENV_SRC				=	$(ENV_SRC_DIR)/env_parse.c

TKNSE_SRC			=	$(TKNSE_SRC_DIR)/tokenise.c \
						$(TKNSE_SRC_DIR)/punctuation.c \
						$(TKNSE_SRC_DIR)/remove_empties.c

EXEC_SRC			=	$(EXEC_SRC_DIR)/execution.c \
						$(EXEC_SRC_DIR)/redirection.c \
						$(EXEC_SRC_DIR)/pipes.c

SIGNALS_SRC			=	$(SIGNALS_SRC_DIR)/sigint.c

EXPND_SRC			=	$(EXPND_SRC_DIR)/expansion.c \
						$(EXPND_SRC_DIR)/convertion.c

MINISHELL_SRC		=	main.c $(ENV_SRC) $(UTILS_SRC) $(BUILTINS_SRC) \
						$(ENV_OP_SRC) $(TKN_SRC) $(TKNSE_SRC) $(EXEC_SRC) \
						$(EXPND_SRC) $(SIGNALS_SRC)

VALGRIND =	valgrind --leak-check=full --show-leak-kinds=all  --suppressions=readline.supp
 
MINISHELL_OBJ		=	$(MINISHELL_SRC:%.c=obj/minishell/%.o)

all:				$(NAME)

$(MINISHELL_OBJ):	obj/minishell/%.o: %.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@ 

$(LIBFT_FILE):
					$(MAKE_LIB) 42_libft
 
$(NAME):			$(MINISHELL_OBJ) $(LIBFT_FILE) 
					$(CC) $(CFLAGS) $(MINISHELL_OBJ) $(LDFLAGS) -lreadline -lncurses -o $@
 
lib_clean:
					$(MAKE_LIB) 42_libft clean
 
lib_fclean:
					$(MAKE_LIB) 42_libft fclean
 
clean:				lib_clean
					rm -rf obj
 
fclean:				clean lib_fclean
					$(RM) $(NAME)

val:				$(NAME)
					$(VALGRIND) ./$(NAME)
 
re:					fclean all
 
.PHONY:				all lib_clean lib_fclean clean fclean re val
