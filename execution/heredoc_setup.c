#include	"minishell.h"

int	count_heredocs(t_data *data)
{
	t_tkn	*tkn;
	int		len;

	len = 1;
	tkn = data->tkn_list;
	while (tkn)
	{
		if (tkn->type == PIPE)
			len++;
		tkn = tkn->next;
	}
	return (len);
}

int	open_heredocs(t_data *data)
{
	t_tkn	*tkn;
	int		len;
	int		i;

	len = count_heredocs(data->tkn_list);
	data->hrdc = (t_hrdc *)malloc(sizeof(t_hrdc) * len + 1);
	if (!data->hrdc)
		return (1);
	tkn = data->tkn_list;
	i = 0;
	while (tkn)
	{
		if (tkn->type == PIPE)
		{
			i++;
			continue ;
		}
	}
}