/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:00:16 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/23 15:33:40 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

enum Type {
  ARG,
  REDIR
}; 

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_tkn
{
	char			*token;
	int				type;
	struct s_tkn	*next;
}	t_tkn;

void	ft_envprint(t_env *env_list);
t_env	*ft_envnew(void *key, void *value);
void	ft_envadd_front(t_env **env, t_env *new);
int		ft_envsize(t_env *env);
t_env	*ft_envlast(t_env *env);
void	ft_envadd_back(t_env **env, t_env *new);
void	ft_envdelone(t_env *env, void (*del)(void *));
void	ft_envclear(t_env **env);
void	ft_enviter(t_env *env, void (*f)(void *));

void	ft_tknadd_back(t_tkn **tkn, t_tkn *new);
void	ft_tknadd_front(t_tkn **tkn, t_tkn *new);
void	ft_tknclear(t_tkn **tkn);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_tkniter(t_tkn *tkn, void (*f)(void *));
t_tkn	*ft_tknlast(t_tkn *tkn);
t_tkn	*ft_tknnew(char *token, int type);
void	ft_tknprint(t_tkn *tkn_list);
int		ft_tknsize(t_tkn *tkn);

char	*ft_strglue(char *s1, char *s2);

t_env	*parse_env(char **env);
int		ft_echo(char **args);
char	**lst_to_str(t_env *env);
int		print(char *str);

t_tkn	*tokenisation(char *str);
t_tkn 	*tokenise(char *str);

#endif