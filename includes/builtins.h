/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:10:55 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/05 15:40:23 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		call(char **args, t_env	*env_list);
int		ft_echo(char **args);
int		ft_env(char **args, t_env *env_list);
int		ft_unset(char **args, t_env *export);
int		ft_pwd(t_env *env_list);
int		ft_cd(char **args, t_env *env);
int		ft_exit(char **args, t_env *env);

int		equal_plus(char	*args, t_env *export, char *plus);
int		equal_plus_helper(char *tmp, t_env *export, t_env *find, char *key);
int		equal_only(char	*args, t_env *export, char *equal);
int		equal_only_helper(char *value, t_env *export, t_env *find, char *key);
int		no_equal(char *args, t_env *export);
int		ft_export(char **args, t_env *env_list);

#endif