/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:29:45 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/09 23:21:45 by svoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*one;
	unsigned char	*two;
	size_t			i;

	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	i = 0;
	while ((i < n && one[i]) || (i < n && two[i]))
	{
		if (one[i] > two[i] || one[i] < two[i])
			return (one[i] - two[i]);
		i++;
	}
	return (0);
}

/*
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	else if ((*s1 != *s2) || !*s1)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (ft_strncmp(++s1, ++s2, --n));
}
*/