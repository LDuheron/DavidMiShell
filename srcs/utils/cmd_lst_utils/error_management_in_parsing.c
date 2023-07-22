/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management_in_parsing.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:50:47 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/22 13:15:57 by lduheron         ###   ########.fr       */
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
		if ((*tokens)->dollars_tab != NULL)
			free((*tokens)->dollars_tab);
		free(*tokens);
		*tokens = tmp;
	}
}

int	error_malloc(t_data_lexing *data_lexing)
{
	ft_putendl_fd("DavidMishell: error malloc", 2);
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
