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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	ft_envprint(t_env *env_list);
t_env	*ft_envnew(void *key, void *value);
void	ft_envadd_front(t_env **env, t_env *new);
int		ft_envsize(t_env *env);
t_env	*ft_envlast(t_env *env);
void	ft_envadd_back(t_env **env, t_env *new);
void	ft_envdelone(t_env *env, void (*del)(void *));
void	ft_envclear(t_env **env);
void	ft_enviter(t_env *env, void (*f)(void *));
t_env	*parse_env(char **env);
int		ft_echo(char **args);
char	**lst_to_str(t_env *env);
int		print(char *str);

#endif