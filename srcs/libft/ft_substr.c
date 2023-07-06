/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:29:45 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/06 12:41:53 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*s_start;
	char		*sub_s;
	size_t		i;
	size_t		s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen((char *)s);
	if (s_len < start)
		return (ft_strdup(""));
	else if (len > s_len - start)
		len = s_len - start;
	sub_s = malloc(len + 1);
	if (!sub_s)
		return (NULL);
	s_start = (char *)s + start;
	i = 0;
	while (i < len)
	{
		sub_s[i] = s_start[i];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}
