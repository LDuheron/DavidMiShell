/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management_in_parsing.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:50:47 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/19 12:51:27 by lduheron         ###   ########.fr       */
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
	if (data_lexing->line)
		free(data_lexing->line);
	return (ERROR_MALLOC);
}

int	free_data_lexing(t_data_lexing *data_lexing)
{
	free(data_lexing->line);
	return (ERROR);
}

/* exit code shall be 2 for such error 
** added data structure here to save the exit_code */
int	error_syntax(t_data *data, t_tokens **tokens, t_tokens *tmp)
{
	ft_putstr_fd("DavidMishell: syntax error near unexpected token ", 2);
	if (tmp == NULL)
		ft_putendl_fd("`newline'", 2);
	else if (tmp->type == PIPE)
		ft_putendl_fd(convert_type_to_char(tmp->type), 2);
	else
		ft_putendl_fd(tmp->content, 2);
	if (tokens)
		free_token_structure(tokens);
	data->exit_code = 2;
	return (ERROR_SYNTAX);
}
/*
int	error_syntax(t_data *data, t_tokens **tokens, t_tokens *tmp)
{
	if (tmp == NULL)
		printf("minishell: syntax error near unexpected token `newline'\n");
	else if (tmp->type == PIPE)
		printf("minishell: syntax error near unexpected token '%s'\n",
			convert_type_to_char(tmp->type)); 
	else
		printf("minishell: syntax error near unexpected token '%s'\n",
			tmp->content);
	if (tokens)
		free_token_structure(tokens);
	data->exit_code = 2;
	return (ERROR_SYNTAX);
}
*/
