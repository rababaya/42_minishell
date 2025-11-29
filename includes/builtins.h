/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:10:55 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/15 15:38:27 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_data	t_data;

int		call(t_data *data);
int		ft_echo(t_data *data);
int		ft_env(t_data *data);
int		ft_unset(t_data *data);
int		ft_pwd(t_data *data);
int		ft_cd(t_data *data);
int		ft_exit(t_data *data);

int		ft_export(t_data *data);
int		equal_plus(char	*args, t_env *export, char *plus);
int		equal_plus_helper(char *tmp, t_env *export, t_env *find, char *key);
int		equal_only(char	*args, t_env *export, char *equal);
int		equal_only_helper(char *value, t_env *export, t_env *find, char *key);
int		no_equal(char *args, t_env *export);

#endif