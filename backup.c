#include "minishell.h"


int	handle_append_red_out(t_tkn **list, char *str, int *i)
{
	(void)list;
	(void)str;
	(*i)++;
	(void)i;
	return (0);
}

int	handle_red_in(t_tkn **list, char *str, int *i)
{
	(void)list;
	(void)str;
	(*i)++;
	(void)i;
	return (0);
}

int	handle_redir(t_tkn **list, char *str, int *i)
{
	(void)list;
	(void)str;
	(*i)++;
	(void)i;
	return (0);
}

int	handle_single_q(t_tkn **list, char *str, int *i)
{
	(void)list;
	(void)str;
	(*i)++;
	(void)i;
	return (0);
}

int	handle_double_q(t_tkn **list, char *str, int *i)
{
	(void)list;
	(void)str;
	(*i)++;
	(void)i;
	return (0);
}

int	handle_heredoc(t_tkn **list, char *str, int *i)
{
	(void)list;
	(void)str;
	(*i)++;
	(void)i;
	return (0);
}


t_tkn *token_ape(char *str)
{
	char	*buf;
	t_tkn	*res;
	t_tkn	*tmp;
	int		i;
	int		j;

	i = 0;
	res = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
			handle_single_q(&res, str, &i);
		else if (str[i] == '\"')
			handle_double_q(&res, str, &i);
		else if (str[i] == '<' && str[i + 1] == '<')
			handle_heredoc(&res, str, &i);
		else if (str[i] == '<')
			handle_red_in(&res, str, &i);
		else if (str[i] == '>' && str[i + 1] == '>')
			handle_append_red_out(&res, str, &i);
		else if (str[i] == '>')
			handle_redir(&res, str, &i);
		else
		{
			while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
				i++;
			j = 0;
			while (str[i + j] && str[i + j] != ' ' && !(str[i + j] >= 9 && str[i + j] <= 13))
				j++;
			buf = ft_substr(str + i, i, j - 1);
			tmp = ft_tknnew(buf, 0);
			if (!tmp)
				return (NULL);
			ft_tknadd_back(&res, tmp);
			i += j;
		}

	}
	return (res);
}