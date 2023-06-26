/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management_in_parsing.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:50:47 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/23 16:15:49 by lduheron         ###   ########.fr       */
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
	free(data_lexing->line);
	return (ERROR_MALLOC);
}

int	free_data_lexing(t_data_lexing *data_lexing)
{
	free(data_lexing->line);
	return (ERROR);
}

int	error_syntax(t_tokens **tokens, int type)
{
	if (type == PIPE)
		printf("minishell: syntax error near unexpected token '|'\n");
	else if (type == SIMPLE_IN)
		printf("minishell: syntax error near unexpected token '<'\n");
	else if (type == SIMPLE_OUT)
		printf("minishell: syntax error near unexpected token '>'\n");
	else if (type == DOUBLE_IN)
		printf("minishell: syntax error near unexpected token '<<'\n");
	else if (type == DOUBLE_OUT)
		printf("minishell: syntax error near unexpected token '>>'\n");
	if (tokens)
		free_token_structure(tokens);
	return (ERROR_SYNTAX);
}
