#include	"minishell.h"

t_ast	*ft_astnew(t_tkn *cmd, int type)
{
	t_ast	*res;

	res = (t_ast *)malloc(sizeof(t_ast));
	if (!res)
		return (NULL);
	res->left = NULL;
	res->right = NULL;
	res->cmd = cmd;
	res->type = type;
	return (res);
}

t_tkn	*next_pipe(t_tkn *tkn)
{
	while (tkn && tkn->type != PIPE)
		tkn = tkn->next;
	return (tkn);
}

t_ast	*parse_ast(t_tkn *now, t_tkn *prev)
{
	t_ast	*res;
	
	if (!next_pipe(now))
		return (ft_astnew(now, CMD));
	res = ft_astnew(NULL, PIPE);
	if (!res)
		return (NULL);
	res->left = prev;
	res->right = parse_ast()


}