/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:40:20 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/11/12 15:49:15 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define ASR_H

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
	t_ast	*left;
	t_ast	*right;
	t_tkn	*tkn;
	int		type;
}	t_ast;

#endif