/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:34:44 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/19 12:28:00 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* GET_CONTENT : This function copies "size" characters from the source "src"
** to the destination "dst", starting from the position indicated by "start".
*/
int	get_content(char *dst, char *src, unsigned int size, unsigned int start)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = start;
	if (size > 0)
	{
		while (src[i] && j < size)
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
	}
	return (0);
}

void	init_data_lexing_structure(t_data_lexing *data_lexing, char *argv)
{
	data_lexing->line = NULL;
	data_lexing->line = ft_strjoin_content(data_lexing->line, argv);
	data_lexing->len = ft_strlen(data_lexing->line);
	data_lexing->d_tab_tmp = NULL;
	data_lexing->pos = 0;
}

/* IS_REDIRECTION: This function returns the corresponding enum_type_token
** code if the given string is a redirection, which can be <, <<, >>, or >>.
** If the string is not a redirection, it returns 0.
*/
int	is_redirection(t_data_lexing *data_lexing)
{
	int	type;

	type = N_DEF;
	if (data_lexing->line && data_lexing->line[data_lexing->pos])
	{
		if (data_lexing->line[data_lexing->pos] == '<')
		{
			type = SIMPLE_IN;
			if (data_lexing->line[data_lexing->pos + 1] == '<')
				type = DOUBLE_IN;
		}
		else if (data_lexing->line[data_lexing->pos] == '>')
		{
			type = SIMPLE_OUT;
			if (data_lexing->line[data_lexing->pos + 1]
				&& data_lexing->line[data_lexing->pos + 1] == '>')
				type = DOUBLE_OUT;
		}
		else
			type = N_DEF;
	}
	return (type);
}

/* IS_NOT_INTERPRETED_DOLLAR: This function searches if the given dollar
** sign ($) is between single quotes, indicating that it is not to be
** interpreted.
*/
int	is_not_interpreted_dollar(char *str, int pos_dollar)
{
	int	i;
	int	flag;

	i = 0;
	flag = OUT;
	while (str[i] && i < pos_dollar)
	{
		if (is_single_quote(str[i]))
		{
			if (flag == IN)
				flag = OUT;
			else
				flag = IN;
		}
		i++;
	}
	if (flag == IN)
		return (1);
	return (OUT);
}

void	ft_lstadd_back_tokens(t_tokens **lst, t_tokens *new)
{
	t_tokens	*tmp;

	tmp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}
