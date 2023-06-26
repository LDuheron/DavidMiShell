/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:41:24 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/22 17:36:03 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// IS_FORBIDDEN : Returns 1 if c is \();/
int	is_forbidden(char c)
{
	return (c == 92 || c == '(' || c == ')' || c == ';' || c == 47);
}

int	is_sign(char c)
{
	return (c == '+' || c == '-');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v');
}
