/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:17:07 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/22 14:17:39 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* WHICH NEW TOKEN : This function redirects the given input to the appropriate
** lexing function to create a token. It returns 0 in case of an error.
*/
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
		ft_putstr_fd("DavidMishell: syntax error near unexpected token ", 2);
		ft_putendl_fd(&data_lexing->line[data_lexing->pos + 1], 2);
		return (0);
	}
	ft_putendl_fd("DavidMishell: error malloc", 2);
	return (0);
}

/* FIND TYPE : This function identifies and returns the type of the given input.
** In case of an error, it returns N_DEF.
*/
int	find_type(t_data_lexing **data_lexing)
{
	int	type;

	type = N_DEF;
	if (is_dollar((*data_lexing)->line[(*data_lexing)->pos]) == 1)
		type = WORD;
	else if ((*data_lexing)->line[(*data_lexing)->pos] == 124)
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

/* LEXING FUNCTION : This function takes a string as input and efficiently
** breaks it down into tokens. These tokens are then stored in a specialized
** linked list for further processing.
*/

int	lexing_helper(t_data_lexing *data_lexing, t_tokens **token,
	t_tokens *tmp_token)
{
	int	len;

	len = 0;
	while (data_lexing->pos < data_lexing->len)
	{
		len = 0;
		while (is_space(data_lexing->line[data_lexing->pos]) == 1)
			data_lexing->pos++;
		tmp_token = which_new_token(data_lexing);
		if (tmp_token == 0)
		{
			free(data_lexing->line);
			return (ERROR);
		}
		len = tmp_token->len;
		ft_lstadd_back_tokens(token, tmp_token);
		data_lexing->pos += len;
		while ((data_lexing->pos < data_lexing->len)
			&& is_space(data_lexing->line[data_lexing->pos]) == 1)
			data_lexing->pos++;
	}
	return (SUCCESS);
}

int	lexing(t_tokens **token, char *buffer)
{
	t_data_lexing	data_lexing;
	t_tokens		*tmp_token;

	tmp_token = NULL;
	if (check_line(buffer) == ERROR_SYNTAX)
		return (ERROR_SYNTAX);
	init_data_lexing_structure(&data_lexing, buffer);
	if (!lexing_helper(&data_lexing, token, tmp_token))
		return (ERROR);
	free(data_lexing.line);
	return (SUCCESS);
}
