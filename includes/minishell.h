/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:00:16 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/15 15:37:40 by rababaya         ###   ########.fr       */
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
# include "utils.h"
# include "tokenisation.h"

typedef struct s_data
{
	t_env	*env_list;
	t_tkn	*tkn_list;
	char	**args;
}	t_data;

t_env	*parse_env(char **env);
char	**lst_to_str(t_env *env);

#endif