/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:34:57 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/19 13:28:27 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*single_dollar_trimming(char *buffer)
{
	int	i;

	i = 0;
	if (nb_dollar(buffer) == 0)
		return (buffer);
	while (buffer && buffer[i] && buffer[i + 1])
	{
		if (is_single_quote(buffer[i]))
			i += single_quote_management(buffer, i);
		else if (buffer[i + 1] && is_double_quote(buffer[i]))
			i += double_quote_management(buffer, i);
		if (buffer && buffer[i] && buffer[i + 1] && buffer[i] == '$')
		{
			if (is_double_quote(buffer[i + 1])
				|| is_single_quote(buffer[i + 1]))
				i = single_dollar_trimming_utils(buffer, i);
			else
				i++;
		}
		else if (buffer[i] != '\0')
			i++;
	}
	return (buffer);
}

void	quotes_trimming(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (is_double_quote(buffer[i]))
			i = single_quotes_trimming_utils(buffer, i);
		else if (is_single_quote(buffer[i]))
			i = double_quotes_trimming_utils(buffer, i);
		else if (buffer[i] != '\0')
			i++;
	}
}

t_tokens	*new_token_double_quote(t_data_lexing *data_lexing, int size)
{
	char	*content;

	content = NULL;
	if (size > 0)
	{
		content = malloc(sizeof(char *) * (size + 1));
		if (content == NULL)
		{
			ft_putendl_fd("DavidMishell: error malloc", 2);
			free(content);
			return (NULL);
		}
		get_content(content, data_lexing->line, size, data_lexing->pos);
	}
	content = adjust_content(data_lexing, content, size);
	return (add_new_token(data_lexing, content, WORD));
}

t_tokens	*new_token_single_quote(t_data_lexing *data_lexing, int size)
{
	char	*content;

	content = NULL;
	if (size > 0)
	{
		content = malloc(sizeof(char *) * (size + 1));
		if (content == NULL)
		{
			ft_putendl_fd("DavidMishell: error malloc", 2);
			free(content);
			return (NULL);
		}
		get_content(content, data_lexing->line, size, data_lexing->pos);
	}
	content = adjust_content(data_lexing, content, size);
	return (add_new_token(data_lexing, content, WORD));
}
