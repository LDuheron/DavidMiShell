/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:02:45 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/18 17:18:16 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*/
char	*ft_strjoin_content(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	j = -1;
	i = -1;
	if (s1 == NULL)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (join != NULL)
	{
		while (s1[++i] != '\0' && s1 != NULL)
			join[i] = s1[++j];
		j = -1;
		while (s2[++j] != '\0')
			join[i++] = s2[j];
		join[i] = '\0';
	}
	free (s1);
	return (join);
}
