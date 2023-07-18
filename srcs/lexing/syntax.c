/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:08:36 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/18 22:06:23 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_before_redir(int type_current, int type_next)
{
	if (type_next == PIPE)
		if (type_current == SIMPLE_IN || type_current == SIMPLE_OUT
			|| type_current == DOUBLE_IN || type_current == DOUBLE_OUT)
			return (1);
	return (0);
}

int	tok_is_op(t_tokens *tok)
{
	return (tok->type == SIMPLE_IN || tok->type == SIMPLE_OUT
		|| tok->type == DOUBLE_IN || tok->type == DOUBLE_OUT
		|| tok->type == PIPE);
}

// CHECK SYNTAX : This function searches for syntax error related
// to the pipe command such as "|", "||", "cat |" and "| cat". It
// also checks syntax error related to redirections.

int	check_syntax(t_tokens **token)
{
	t_tokens	*tmp;

	tmp = *token;
	if (tmp && tmp->type && tmp->type == PIPE)
		return (error_syntax(token, tmp));
	while (tmp)
	{
		if (!tmp->next && tok_is_op(tmp) && tmp->content == NULL)
			return (error_syntax(token, tmp));
		else if (tok_is_op(tmp) && tmp->content == NULL
			&& tmp->next && tok_is_op(tmp->next))
			if (is_pipe_before_redir(tmp->type, tmp->next->type) == 1)
				return (error_syntax(token, tmp->next));
		tmp = tmp->next;
	}
	return (SUCCESS);
}

// CHECK OPEN S QUOTE : This function ensures that the single quotes
// in the given line are properly closed. It returns an error code
// if there is an open single quote at the end of the string.

int	check_open_s_quote(char *str, int i)
{
	i++;
	while (str[i] && is_single_quote(str[i]) == 0)
		i++;
	if (str[i] == '\0')
	{
		printf("minishell: syntax error single quote\n");
		return (ERROR_SYNTAX);
	}
	if (is_single_quote(str[i]) == 1)
				i++;
	return (i);
}

// CHECK OPEN D QUOTE : This function ensures that the double quotes
// in the given line are properly closed. It returns an error code
// if there is an open double quote at the end of the string.

int	check_open_d_quote(char *str, int i)
{
	i++;
	while (str[i] && is_double_quote(str[i]) == 0)
		i++;
	if (str[i] == '\0')
	{
		printf("minishell: syntax error double quote\n");
		return (ERROR_SYNTAX);
	}
	if (is_double_quote(str[i]) == 1)
		i++;
	return (i);
}

// CHECK_LINE: This function ensures that all quotes in the given
// line are properly closed. It returns an error code if there is
// an open quote at the end of the string.

int	check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_single_quote(str[i]) == 1)
			i = check_open_s_quote(str, i);
		else if (is_double_quote(str[i]) == 1)
			i = check_open_d_quote(str, i);
		else
			i++;
		if (i == ERROR_SYNTAX)
			return (ERROR_SYNTAX);
	}
	return (SUCCESS);
}
