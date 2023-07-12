/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:46:13 by svoi              #+#    #+#             */
/*   Updated: 2023/07/12 18:08:15 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ..this function wasn't tested yet !! */
int	ft_unset(t_data *data, t_cmd_lst *cmd_lst)
{
	int		i;
	int		j;

	if (cmd_lst->cmd_node->argument[1] != NULL)
	{
		i = 0;
		while (data->m_envp[i])
		{
			if (ft_strncmp(data->m_envp[i],
					cmd_lst->cmd_node->argument[1],
					ft_strchr_i(data->m_envp[i], '=')) == 0)
			{
				free(data->m_envp[i]);
				j = i;
				while (data->m_envp[++j])
					data->m_envp[j - 1] = data->m_envp[j];
				data->m_envp[j - 1] = NULL;
				break ;
			}
			i++;
		}
	}
	data->exit_code = 0;
	return (0);
}
