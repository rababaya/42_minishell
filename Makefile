CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -I 42_libft -I includes -g3
RM					=	rm -f
NAME				=	minishell
CHECKER				=	checker

LIBFT_FILE			=	42_libft/libft.a
LDFLAGS     		=	-L 42_libft -l ft
MAKE_LIB			=	make -C

LIST_SRC_DIR		=	list_operations
TKN_SRC_DIR			=	tkn_operations
ENV_SRC_DIR			=	env
UTILS_SRC_DIR		=	utils
BUILTINS_SRC_DIR	=	builtins
TKNSE_SRC_DIR		=	tokenisation
EXPND_SRC_DIR		=	expansion

LIST_SRC			=	$(LIST_SRC_DIR)/ft_envadd_back.c \
						$(LIST_SRC_DIR)/ft_envclear.c \
						$(LIST_SRC_DIR)/ft_envsize.c \
						$(LIST_SRC_DIR)/ft_envadd_front.c \
						$(LIST_SRC_DIR)/ft_envlast.c \
						$(LIST_SRC_DIR)/ft_envprint.c \
						$(LIST_SRC_DIR)/ft_envnew.c

TKN_SRC				=	$(TKN_SRC_DIR)/ft_tknadd_back.c \
						$(TKN_SRC_DIR)/ft_tknadd_front.c \
						$(TKN_SRC_DIR)/ft_tknclear.c \
						$(TKN_SRC_DIR)/ft_tknsize.c \
						$(TKN_SRC_DIR)/ft_tknlast.c \
						$(TKN_SRC_DIR)/ft_tknprint.c \
						$(TKN_SRC_DIR)/ft_tknnew.c \

BUILTINS_SRC		=	$(BUILTINS_SRC_DIR)/builtin_call.c \
						$(BUILTINS_SRC_DIR)/echo.c 

UTILS_SRC			=	$(UTILS_SRC_DIR)/print.c \
						$(UTILS_SRC_DIR)/ft_strglue.c

ENV_SRC				=	$(ENV_SRC_DIR)/env_parse.c

TKNSE_SRC			=	$(TKNSE_SRC_DIR)/tokenise.c

EXPND_SRC			=	$(EXPND_SRC_DIR)/expand.c

MINISHELL_SRC		=	main.c $(ENV_SRC) $(UTILS_SRC) $(BUILTINS_SRC) \
						$(LIST_SRC) $(TKN_SRC) $(TKNSE_SRC) $(EXPND_SRC)
 
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
