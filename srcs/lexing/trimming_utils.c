/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimming_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:04:45 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/17 12:05:33 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_dollar_trimming_utils(char *buffer, int i)
{
	int	j;

	j = i;
	while (buffer[j])
	{
		buffer[j] = buffer[j + 1];
			j++;
	}
	buffer[j] = 0;
	if (is_single_quote(buffer[i + 1]))
		i += single_quote_management(buffer, i) - 1;
	else if (buffer[i + 1] && is_double_quote(buffer[i + 1]))
		i += double_quote_management(buffer, i);
	return (i);
}

int	single_quotes_trimming_utils(char *buffer, int i)
{
	int	j;

	j = i;
	while (buffer[j])
	{
		buffer[j] = buffer[j + 1];
		j++;
	}
	buffer[j] = 0;
	while (buffer[i] && is_double_quote(buffer[i]) == 0)
		i++;
	j = i;
	while (buffer[j])
	{
		buffer[j] = buffer[j + 1];
		j++;
	}
	buffer[j] = 0;
	return (i);
}

int	double_quotes_trimming_utils(char *buffer, int i)
{
	int	j;

	j = i;
	while (buffer[j])
	{
		buffer[j] = buffer[j + 1];
		j++;
	}
	buffer[j] = 0;
	while (buffer[i] && is_single_quote(buffer[i]) == 0)
		i++;
	j = i;
	while (buffer[j])
	{
		buffer[j] = buffer[j + 1];
		j++;
	}
	buffer[j] = 0;
	return (i);
}
