#include	"minishell.h"

int	count_heredocs(t_data *data)
{
	t_tkn	*tkn;
	int		len;
	int		hrdc;

	len = 0;
	tkn = data->tkn_list;
	hrdc = 0;
	while (tkn)
	{
		if (tkn->type == PIPE)
		{
			if (hrdc)
				len++;
			hrdc = 0;
		}
		if (tkn->type == HRDC)
			hrdc++;
		tkn = tkn->next;
	}
	if (hrdc)
		len++;
	return (len);
}

int	open_heredocs(t_data *data)
{
	t_tkn	*tkn;
	int		i;
	int		init;
	int		ret;

	i = count_heredocs(data);
	if (!i)
		return (0);
	data->hrdc = (t_hrdc *)malloc(sizeof(t_hrdc) * i);
	if (!data->hrdc)
		return (1);
	tkn = data->tkn_list;
	i = 0;
	init = 0;
	while (tkn)
	{
		if (tkn->type == PIPE && init)
		{
			data->hrdc[i++].tkn = tkn;
			init = 0;
		}
		else if (tkn->type == HRDC)
		{
			if (init && (data->hrdc)[i].fd != 0)
				close((data->hrdc)[i].fd);
			ret = heredoc(data, tkn, i);
			if (ret)
				return (ret);
			init = 1;
		}
		tkn = tkn->next;
	}
	if (init)
		data->hrdc[i].tkn = tkn;
	return (0);
}
