#include "minishell.h"

void	ft_tkndelone(t_tkn **lst, ft_tkn *tkn)
{
	t_tkn	*tmp;

	if (lst && tkn)
	{
		tmp = *lst;
		while (tmp->next && tmp->next != tkn)
			tmp = tmmp->next;
		tmp->next = tkn->next;
		free(tkn->token);
		free(tkn);
	}
}
