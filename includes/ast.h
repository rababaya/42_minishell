/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:40:20 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/11/15 15:09:24 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

enum	e_node
{
	PIPE,
	AND,
	OR,
	SUBSH,
	CMD
};

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	t_tkn	*cmd;
	int		type;
}	t_ast;

#endif