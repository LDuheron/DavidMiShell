/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:44:00 by svoi              #+#    #+#             */
/*   Updated: 2023/07/05 23:45:07 by svoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->m_envp[i] != NULL)
	{
		// DEBUG //
		//printf("[%d] : '%s'\n", i, data->m_envp[i]);
		ft_putendl_fd(data->m_envp[i], 1);
		i++;
	}
	data->exit_return = 0; 
	return (0);
}
