/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:49:32 by sbocanci          #+#    #+#             */
/*   Updated: 2023/06/29 17:27:50 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i]) 
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}
