/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:58:52 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/22 14:24:50 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ASCII CODE FOR QUOTES : 
// " == 34
// ' == 39

int	is_double_quote(char c)
{
	return (c == 34);
}

int	is_single_quote(char c)
{
	return (c == 39);
}

int	is_quote(char c)
{
	return (c == 34 || c == 39);
}

// DOUBLE_QUOTE_MANAGEMENT : Starting from an opening double quote, 
// searches for the closing single quote and return 
// the size of the buffer to parse.

int	double_quote_management(char *line, int start)
{
	int	i;
	int	size;

	i = start + 1;
	size = 1;
	while (line[i] && is_double_quote(line[i]) == 0)
	{
		size++;
		i++;
	}
	return (size + 1);
}

// SINGLE_QUOTE_MANAGEMENT : Starting from an opening single quote, 
// searches for the closing single quote and return 
// the size of the buffer to parse.

int	single_quote_management(char *line, int start)
{
	int	i;
	int	size;

	i = start + 1;
	size = 1;
	while (line[i] && is_single_quote(line[i]) == 0)
	{
		size++;
		i++;
	}
	return (size + 1);
}
