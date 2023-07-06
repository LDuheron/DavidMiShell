/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:14:35 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/06 16:38:01 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	copy_word(char **spt, char const *s, size_t word, size_t len)
{
	size_t			i;

	spt[word] = (char *)malloc(sizeof(*spt[word]) * (len + 1));
	if (!spt[word])
	{
		while (word--)
			free(spt[word]);
		free(spt[word]);
		free(spt);
		spt = NULL;
		return ;
	}
	i = 0;
	while (i < len && s[i])
	{
		spt[word][i] = s[i];
		i++;
	}
	spt[word][i] = '\0';
}

static void	to_split(char **spt, char const *s, char c)
{
	size_t				i;
	size_t				tmp;
	size_t				word;

	word = 0;
	i = 0;
	tmp = 0;
	while (i < ft_strlen(s))
	{
		while (s[i] == c && i < ft_strlen(s))
			i++;
		tmp = i;
		while (s[i] != c && i < ft_strlen(s))
			i++;
		if (i > tmp)
		{
			copy_word(spt, &s[tmp], word, i - tmp);
			word++;
		}
	}
	spt[word] = (void *)0;
}

char	**ft_split(char const *s, char c)
{
	char		**spl;
	size_t		words;
	size_t		i;

	if (!s)
		return (NULL);
	words = 0;
	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	spl = (char **)malloc(sizeof(char *) * (words + 1));
	if (!spl)
		return (NULL);
	if (words == 0)
	{
		spl[words] = (void *)0;
		return (spl);
	}
	to_split(spl, s, c);
	return (spl);
}
