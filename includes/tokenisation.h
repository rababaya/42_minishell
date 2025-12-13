/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:13:52 by rababaya          #+#    #+#             */
/*   Updated: 2025/12/13 14:01:00 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISATION_H
# define TOKENISATION_H

typedef struct s_tkn
{
	char			*token;
	int				type;
	struct s_tkn	*next;
}	t_tkn;

enum e_type
{
	ARG,
	RED_OUT,
	RED_IN,
	APPND,
	PIPE,
	HRDC
};

void	ft_tknadd_back(t_tkn **tkn, t_tkn *new);
void	ft_tknadd_front(t_tkn **tkn, t_tkn *new);
void	ft_tknclear(t_tkn **tkn);
void	ft_tkndelone(t_tkn **lst, t_tkn *tkn);
void	ft_tkniter(t_tkn *tkn, void (*f)(void *));
t_tkn	*ft_tknlast(t_tkn *tkn);
t_tkn	*ft_tknnew(char *token, int type);
void	ft_tknprint(t_tkn *tkn_list);
int		ft_tknsize(t_tkn *tkn);

int		tokenise(t_tkn **tkn, char *str);
int		check_punctuation(char *str);
void	remove_empties(t_tkn **tkn);

int		expand(t_tkn *tkn, t_env *env);
char	**convertion(t_tkn *tkn, int len);
#endif
