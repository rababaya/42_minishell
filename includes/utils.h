/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:09:07 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/05 16:11:43 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	*ft_my_realloc(void *ptr, size_t old_size, size_t new_size);
void	free_split(char ***s);
char	*ft_strglue(char *s1, char *s2);
int		print(char *str);
int		ft_iswhitespace(char c);

#endif
