/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_buffer_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:33:08 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/03 15:44:19 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	empty_buffer(char *str)
{
	while (*str)
	{
		if (!is_space(*str))
			return (false);
		str++;
	}
	return (true);
}
