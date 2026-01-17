/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 21:16:08 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/17 16:01:43 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	process_heredoc(t_data *data, t_tkn *tkn, int i, int init)
{
	int	ret;

	if (init && (data->hrdc)[i].fd != 0)
		close((data->hrdc)[i].fd);
	ret = heredoc(data, tkn, i);
	if (ret)
		return (ret);
	return (0);
}

static int	process_tokens(t_data *data, int *i, int *init)
{
	t_tkn	*tkn;
	int		ret;

	tkn = data->tkn_list;
	while (tkn)
	{
		if (tkn->type == PIPE && *init)
		{
			data->hrdc[(*i)++].tkn = tkn;
			*init = 0;
		}
		else if (tkn->type == HRDC)
		{
			ret = process_heredoc(data, tkn, *i, *init);
			if (ret)
				return (ret);
			*init = 1;
		}
		tkn = tkn->next;
	}
	if (*init)
		data->hrdc[*i].tkn = tkn;
	return (0);
}

int	open_heredocs(t_data *data)
{
	int	i;
	int	init;

	i = count_heredocs(data);
	if (!i)
		return (0);
	data->hrdc = (t_hrdc *)malloc(sizeof(t_hrdc) * i);
	if (!data->hrdc)
		return (1);
	i = 0;
	init = 0;
	return (process_tokens(data, &i, &init));
}
