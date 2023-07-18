/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management_in_parsing.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:50:47 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/18 22:24:37 by svoi             ###   ########.fr       */
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

/* exit code shall be 2 for such error 
** added data structure here to save the exit_code */
int	error_syntax(t_data *data, t_tokens **tokens, t_tokens *tmp)
{
	printf("tmp->content %s\n", tmp->content);
	
	if (tmp->type != WORD)
		printf("minishell: syntax error near unexpected token '%s'\n", convert_type_to_char(tmp->type));
	else if (tmp->content == NULL)
		printf("minishell: syntax error near unexpected token `newline'\n");
	else
		printf("minishell: syntax error near unexpected token '%s'\n", tmp->content);
	if (tokens)
		free_token_structure(tokens);
	data->exit_code = 2;
	return (ERROR_SYNTAX);
}
/*
int	error_syntax(t_tokens **tokens, t_tokens *tmp)
{
	printf("tmp->content %s\n", tmp->content);
	
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
*/
// else if (tmp->content == NULL)
// 	printf("minishell: syntax error near unexpected token `newline'\n");