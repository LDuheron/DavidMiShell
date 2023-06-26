/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:12:35 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/22 15:28:10 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	is_dollar(char c)
{
	return (c == 36);
}

// IS_METACHARACTER : This function returns 1, if the character sent
// is a metacharacter : |&;<>\()`\n\tspace
// A metacharacter causes termination of a word unless it is quoted.

int	is_metacharacter(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == 38 || c == 59 || c == 60 || c == 62
		|| c == 92 || c == 96 || is_pipe(c) == 1)
		return (1);
	return (0);
}

int	is_number(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_pipe(char c)
{
	return (c == 124);
}
