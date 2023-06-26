/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:08:36 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/22 17:54:54 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// CHECK REDIRECTION CONTENT : This function searches for syntax error related
// to redirections such as redirections not related to any file or "<>", ">>>",
// "<< <<" and ">|".

int	check_redirection_content(t_tokens **token)
{
	t_tokens	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == SIMPLE_IN || tmp->type == SIMPLE_OUT
			|| tmp->type == DOUBLE_IN || tmp->type == DOUBLE_OUT)
		{
			if (tmp->content == NULL)
				return (error_syntax(token, (*token)->type));
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

// CHECK SYNTAX : This function searches for syntax error related
// to the pipe command such as "|", "||", "cat |" and "| cat". It
// also checks syntax error related to redirection calling
// check_redirection_content funtion.

int	check_syntax(t_tokens **token)
{
	t_tokens	*tmp;

	tmp = *token;
	if (tmp->type == PIPE)
		return (error_syntax(token, PIPE));
	while (tmp)
	{
		if (tmp->next)
		{
			if (tmp->next->type == PIPE)
				if (!(tmp->next->next) || tmp->type == PIPE
					|| tmp->next->next->type == PIPE)
					return (error_syntax(token, PIPE));
		}
		else
			if (tmp->type == PIPE)
				return (error_syntax(token, PIPE));
		tmp = tmp->next;
	}
	return (check_redirection_content(token));
}

// CHECK OPEN S QUOTE : This function ensures that the single quotes in the
// given line are correctly closed.

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

// CHECK OPEN D QUOTE : This function ensures that the double quotes in the
// given line are correctly closed.

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

// CHECK LINE : This function ensures that all quotes in the given
// line are correctly closed.

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
