/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:17:07 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/23 20:46:44 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// WHICH NEW TOKEN : This function creates a token depending on the type
// of the input.

t_tokens	*which_new_token(t_data_lexing *data_lexing)
{
	int			type;

	type = find_type(&data_lexing);
	if (type == WORD)
		return (lexing_word(data_lexing, WORD));
	else if (type == SIMPLE_IN || type == SIMPLE_OUT)
		return (lexing_redirection(data_lexing, type, 1));
	else if (type == DOUBLE_IN || type == DOUBLE_OUT)
		return (lexing_redirection(data_lexing, type, 2));
	else if (type == SINGLE_QUOTE)
		return (lexing_single_quote(data_lexing));
	else if (type == DOUBLE_QUOTE)
		return (lexing_double_quote(data_lexing));
	else if (type == PIPE)
		return (new_token_pipe());
	else if (is_forbidden(data_lexing->line[data_lexing->pos]) == 1)
	{
		printf("minishell: syntax error near unexpected token '%c'\n",
			data_lexing->line[data_lexing->pos]);
		return (0);
	}
	printf("minishell: error malloc\n");
	return (0);
}

// FIND TYPE : Returns the type of the input.

int	find_type(t_data_lexing **data_lexing)
{
	int	type;

	type = N_DEF;
	if ((*data_lexing)->line[(*data_lexing)->pos] == 124)
		type = PIPE;
	else if (is_single_quote((*data_lexing)->line[(*data_lexing)->pos]) == 1)
		type = SINGLE_QUOTE;
	else if (is_double_quote((*data_lexing)->line[(*data_lexing)->pos]) == 1)
		type = DOUBLE_QUOTE;
	else if (is_redirection(*data_lexing) != N_DEF)
		type = is_redirection(*data_lexing);
	else if (is_metacharacter((*data_lexing)->line[(*data_lexing)->pos]) == 0)
		type = WORD;
	return (type);
}

// LEXING FUNCTION : This function parses the line in tokens
// and store them in a linked list.

int	lexing(t_tokens **token, char *buffer)
{
	int				len;
	t_data_lexing	data_lexing;
	t_tokens		*tmp_token;

	len = 0;
	if (check_line(buffer) == ERROR_SYNTAX)
		return (error_in_line(&data_lexing));
	init_data_lexing_structure(&data_lexing, buffer);
	data_lexing.flag = SUCCESS;
	while (data_lexing.pos < data_lexing.len)
	{
		len = 0;
		while (is_space(data_lexing.line[data_lexing.pos]) == 1)
			data_lexing.pos++;
		tmp_token = which_new_token(&data_lexing);
		if (tmp_token == 0)
			return (free_data_lexing(&data_lexing));
		len = tmp_token->len;
		ft_lstadd_back(token, tmp_token);
		data_lexing.pos += len;
	}
	free(data_lexing.line);
	return (SUCCESS);
}
