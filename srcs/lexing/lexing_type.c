/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:34:38 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/19 10:07:19 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* LEXING_*.c : These functions each find the appropriate
** size of the content and return the corresponding tokens.
*/
t_tokens	*lexing_double_quote(t_data_lexing *data_lexing)
{
	int		size;
	int		i;

	size = double_quote_management(data_lexing->line, data_lexing->pos);
	if (is_space(data_lexing->line[data_lexing->pos + size]) == 1)
		return (new_token_double_quote(data_lexing, size));
	else
	{
		i = size + data_lexing->pos;
		while (data_lexing->line[i]
			&& is_metacharacter(data_lexing->line[i]) == 0)
		{
			if (is_double_quote(data_lexing->line[i]) == 1)
				size += double_quote_management(data_lexing->line, i);
			if (is_single_quote(data_lexing->line[i]) == 1)
				size += single_quote_management(data_lexing->line, i);
			i++;
			size++;
		}
	}
	return (new_token_double_quote(data_lexing, size));
}

t_tokens	*lexing_single_quote(t_data_lexing *data_lexing)
{
	int		size;
	int		i;

	size = single_quote_management(data_lexing->line, data_lexing->pos);
	if (is_space(data_lexing->line[data_lexing->pos + size]) == 1)
		return (new_token_single_quote(data_lexing, size));
	else
	{
		i = size + data_lexing->pos;
		while (data_lexing->line[i]
			&& is_metacharacter(data_lexing->line[i]) == 0)
		{
			if (is_double_quote(data_lexing->line[i]) == 1)
				size += double_quote_management(data_lexing->line, i);
			if (is_single_quote(data_lexing->line[i]) == 1)
				size += single_quote_management(data_lexing->line, i);
			i++;
			size++;
		}
	}
	return (new_token_single_quote(data_lexing, size));
}

t_tokens	*lexing_redirection(t_data_lexing *data_lexing, int type,
	int size_redirection)
{
	data_lexing->pos += size_redirection;
	if (is_space(data_lexing->line[data_lexing->pos]) == 1)
		data_lexing->pos += 1;
	return (lexing_word(data_lexing, type));
}

t_tokens	*lexing_word(t_data_lexing *data_lexing, int type)
{
	int	i;

	i = data_lexing->pos;
	while (data_lexing->line[i] && is_metacharacter(data_lexing->line[i]) == 0
		&& is_space(data_lexing->line[i]) == 0)
	{
		if (is_double_quote(data_lexing->line[i]) == 1)
			i += double_quote_management(data_lexing->line, i);
		else if (is_single_quote(data_lexing->line[i]) == 1)
			i += single_quote_management(data_lexing->line, i);
		else
			i++;
	}
	return (new_token(data_lexing, type, (i - data_lexing->pos)));
}
