/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:41:24 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/19 10:40:57 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* IS_FORBIDDEN : Returns 1 if c is \();/& */
int	is_forbidden(char c)
{
	return (c == 92 || c == '(' || c == ')' || c == ';' || c == 47 || c == 38);
}

int	is_sign(char c)
{
	return (c == '+' || c == '-');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v');
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
