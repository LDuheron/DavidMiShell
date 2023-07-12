/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:44:00 by svoi              #+#    #+#             */
/*   Updated: 2023/07/12 13:52:19 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->m_envp[i])
	{
		/* DEBUG */
		//printf("[%d] : '%s'\n", i, data->m_envp[i]);
		/* ***** */

		ft_putendl_fd(data->m_envp[i], 1);
		i++;
	}
	data->exit_code = 0; 
	return (0);
}
