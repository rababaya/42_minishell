/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ops.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:32:27 by rababaya          #+#    #+#             */
/*   Updated: 2025/10/21 00:41:02 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_OPS_H
# define LIST_OPS_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		ft_envprint(t_env *env_list);
int		ft_exportprint(t_env *export);
t_env	*ft_envnew(void *key, void *value);
void	ft_envadd_front(t_env **env, t_env *new);
int		ft_envsize(t_env *env);
t_env	*ft_envlast(t_env *env);
void	ft_envadd_back(t_env **env, t_env *new);
void	ft_envdelone(t_env **env, char *key);
void	ft_envclear(t_env **env);
void	ft_enviter(t_env *env, void (*f)(void *));
t_env	*ft_envfind(t_env *env_list, char *key);

#endif