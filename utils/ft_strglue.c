/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strglue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:02:43 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/11/01 17:02:44 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strglue(char *s1, char *s2)
{
	char	*res;
	char	*start;
	char	*s1_cpy;

	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	s1_cpy = s1;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (free(s1), NULL);
	start = res;
	while (*s1)
		*(res++) = *(s1++);
	while (*s2)
		*(res++) = *(s2++);
	*res = 0;
	free(s1_cpy);
	return (start);
}
