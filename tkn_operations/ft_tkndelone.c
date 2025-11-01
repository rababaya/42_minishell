#include "minishell.h"

void	ft_tkndelone(t_tkn **lst, ft_tkn *tkn)
{
	t_tkn	*tmp;

	if (lst && tkn)
	{
		tmp = *lst;
		if (tmp == tkn)
		{
			*lst = *lst->next;
			free(tkn->token);
			free(tkn);
			return ;
		}
		while (tmp->next && tmp->next != tkn)
			tmp = tmp->next;
		tmp->next = tkn->next;
		free(tkn->token);
		free(tkn);
	}
}
