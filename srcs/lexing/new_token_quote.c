/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:34:57 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/17 11:39:03 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_dollar_trimming_utils(char *buffer, int i)
{
	int	j;

	j = i;
	while (buffer[j])
	{
		buffer[j] = buffer[j + 1];
			j++;
	}
	buffer[j] = 0;
	if (is_single_quote(buffer[i + 1]))
		i += single_quote_management(buffer, i) - 1;
	else if (buffer[i + 1] && is_double_quote(buffer[i + 1]))
		i += double_quote_management(buffer, i);
	return (i);
}

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

// void	quotes_trimming_copy(char *buffer)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (buffer[i])
// 	{
// 		if (is_double_quote(buffer[i]))
// 		{
// 			j = i;
// 			while (buffer[j])
// 			{
// 				buffer[j] = buffer[j + 1];
// 				j++;
// 			}
// 			buffer[j] = 0;
// 			while (buffer[i] && is_double_quote(buffer[i]) == 0)
// 				i++;
// 			j = i;
// 			while (buffer[j])
// 			{
// 				buffer[j] = buffer[j + 1];
// 				j++;
// 			}
// 			buffer[j] = 0;
// 		}
// 		else if (is_single_quote(buffer[i]))
// 		{
// 			j = i;
// 			while (buffer[j])
// 			{
// 				buffer[j] = buffer[j + 1];
// 				j++;
// 			}
// 			buffer[j] = 0;
// 			while (buffer[i] && is_single_quote(buffer[i]) == 0)
// 				i++;
// 			j = i;
// 			while (buffer[j])
// 			{
// 				buffer[j] = buffer[j + 1];
// 				j++;
// 			}
// 			buffer[j] = 0;
// 		}
// 		else if (buffer[i] != '\0')
// 			i++;
// 	}
// }

// 	quotes_trimming_utils()
// {
	// 
// }

int	quote_trimming_utils(char *buffer, int i)
{
	int j;

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
	return (i);
}

void	quotes_trimming(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	while (buffer[i])
	{
		if (is_double_quote(buffer[i]))
			i = quote_trimming_utils(buffer, i);
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
