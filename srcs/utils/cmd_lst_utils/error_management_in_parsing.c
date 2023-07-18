/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management_in_parsing.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:50:47 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/18 22:05:19 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FREE TOKEN STRUCTURE : Free the elements of a t_tokens structure.

void	free_token_structure(t_tokens **tokens)
{
	t_tokens	*tmp;

	while (*tokens && tokens)
	{
		tmp = (*tokens)->next;
		free((*tokens)->content);
		free(*tokens);
		*tokens = tmp;
	}
}

int	error_malloc(t_data_lexing *data_lexing)
{
	printf("minishell: error malloc\n");
	free(data_lexing->line);
	return (ERROR_MALLOC);
}

int	error_in_line(t_data_lexing *data_lexing)
{
	(void)data_lexing;
	return (ERROR_MALLOC);
}

int	free_data_lexing(t_data_lexing *data_lexing)
{
	free(data_lexing->line);
	return (ERROR);
}

char	*convert_type_to_char(int type)
{
	if (type == SIMPLE_IN)
		return ("<");
	else if (type == SIMPLE_OUT)
		return (">");
	else if (type == DOUBLE_IN)
		return ("<<");
	else if (type == DOUBLE_OUT)
		return (">>");
	else if (type == PIPE)
		return ("|");
	return (ERROR);
}

int	error_syntax(t_tokens **tokens, t_tokens *tmp)
{
	if (tmp->type != WORD)
		printf("minishell: syntax error near unexpected token '%s'\n", convert_type_to_char(tmp->type));
	else if (tmp->content == NULL)
		printf("minishell: syntax error near unexpected token `newline'\n");
	else
		printf("minishell: syntax error near unexpected token '%s'\n", tmp->content);
	if (tokens)
		free_token_structure(tokens);
	return (ERROR_SYNTAX);
}

// else if (tmp->content == NULL)
// 	printf("minishell: syntax error near unexpected token `newline'\n");