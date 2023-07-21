/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:52:55 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/21 18:24:30 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_redir(t_tokens *token)
{
	if (tok_is_redir(token) == 1
		&& (token->content == NULL || token->content[0] == '\0'))
		return (1);
	return (0);
}

int	check_syntax(t_data *data, t_tokens **token)
{
	t_tokens	*tmp;

	tmp = *token;
	if (tmp && tmp->type && tmp->type == PIPE)
		return (error_syntax(data, token, tmp));
	while (tmp)
	{
		if (is_empty_redir(tmp) == 1)
			return (error_syntax(data, token, NULL));
		if (tmp->type == PIPE && (!tmp->next
				|| (tmp->next && tmp->next->type == PIPE)))
			return (error_syntax(data, token, NULL));
		tmp = tmp->next;
	}
	return (SUCCESS);
}

/* CHECK OPEN S QUOTE : This function ensures that the single quotes
** in the given line are properly closed. It returns an error code
** if there is an open single quote at the end of the string.
*/
int	check_open_s_quote(char *str, int i)
{
	i++;
	while (str[i] && is_single_quote(str[i]) == 0)
		i++;
	if (str[i] == '\0')
	{
		ft_putendl_fd("DavidMishell: syntax error single quote", 2);
		return (ERROR_SYNTAX);
	}
	if (is_single_quote(str[i]) == 1)
				i++;
	return (i);
}

/* CHECK OPEN D QUOTE : This function ensures that the double quotes
** in the given line are properly closed. It returns an error code
** if there is an open double quote at the end of the string.
*/
int	check_open_d_quote(char *str, int i)
{
	i++;
	while (str[i] && is_double_quote(str[i]) == 0)
		i++;
	if (str[i] == '\0')
	{
		ft_putendl_fd("DavidMishell: syntax error double quote", 2);
		return (ERROR_SYNTAX);
	}
	if (is_double_quote(str[i]) == 1)
		i++;
	return (i);
}

/* CHECK_LINE: This function ensures that all quotes in the given
** line are properly closed. It returns an error code if there is
** an open quote at the end of the string.
*/

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
