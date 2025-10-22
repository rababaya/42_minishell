/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:00:16 by rababaya          #+#    #+#             */
/*   Updated: 2025/10/21 00:40:55 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "list_ops.h"
# include "builtins.h"

t_env	*parse_env(char **env);
char	**lst_to_str(t_env *env);

void	*ft_my_realloc(void *ptr, size_t old_size, size_t new_size);
void	free_split(char ***s);
int		print(char *str);

#endif