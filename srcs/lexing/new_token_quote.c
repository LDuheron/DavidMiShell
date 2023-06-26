/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:34:57 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/25 14:03:50 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*single_dollar_trimming(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '$' && buffer[i + 1])
		{
			if (is_double_quote(buffer[i + 1]))
			{
				j = i;
				while (buffer[j])
				{
					buffer[j] = buffer[j + 1];
					j++;
				}
				buffer[j] = 0;
				while (buffer[i] && is_double_quote(buffer[i]) == 0)
					i++;
				j = i;
				while (buffer[j])
				{
					buffer[j] = buffer[j + 1];
					j++;
				}
				buffer[j] = 0;
			}
			else if (is_single_quote(buffer[i + 1]))
			{
				j = i;
				while (buffer[j])
				{
					buffer[j] = buffer[j + 1];
					j++;
				}
				buffer[j] = 0;
				while (buffer[i] && is_single_quote(buffer[i]) == 0)
					i++;
				j = i;
				while (buffer[j])
				{
					buffer[j] = buffer[j + 1];
					j++;
				}
				buffer[j] = 0;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (buffer);
}

void	quotes_trimming(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	while (buffer[i])
	{
		if (is_double_quote(buffer[i]))
		{
			j = i;
			while (buffer[j])
			{
				buffer[j] = buffer[j + 1];
				j++;
			}
			buffer[j] = 0;
			while (buffer[i] && is_double_quote(buffer[i]) == 0)
				i++;
			j = i;
			while (buffer[j])
			{
				buffer[j] = buffer[j + 1];
				j++;
			}
			buffer[j] = 0;
		}
		else if (is_single_quote(buffer[i]))
		{
			j = i;
			while (buffer[j])
			{
				buffer[j] = buffer[j + 1];
				j++;
			}
			buffer[j] = 0;
			while (buffer[i] && is_single_quote(buffer[i]) == 0)
				i++;
			j = i;
			while (buffer[j])
			{
				buffer[j] = buffer[j + 1];
				j++;
			}
			buffer[j] = 0;
		}
		else
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
			printf("minishell: error malloc\n");
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
			printf("minishell: error malloc\n");
			free(content);
			return (NULL);
		}
		get_content(content, data_lexing->line, size, data_lexing->pos);
	}
	content = adjust_content(data_lexing, content, size);
	return (add_new_token(data_lexing, content, WORD));
}
	// premier passage ou je supprime dollar si suivi de double quotes
	// compte le nombre de dollar et on malloc le tableau de int
	// single_dollar_trimming(content_tmp);