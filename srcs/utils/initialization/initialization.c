/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:15:20 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/19 11:40:11 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Protection from unsetting env 
**
*/
void	init_envp(t_data *data)
{
	int		count;

	data->m_envp = (char **)malloc(sizeof(char *) * BUFFER);
	if (!data->m_envp)
		return ;
	count = 0;
	while (data->env[count])
	{
		data->m_envp[count] = ft_strdup(data->env[count]);
		count++;
	}
	while (count < BUFFER)
		data->m_envp[count++] = NULL;
}

void	init_data(t_data *data, char **env)
{
	data->env = env;
	data->m_envp = NULL;
	init_envp(data);
	data->path_dirs = NULL;
	data->cmd_lst = NULL;
	data->token = NULL;
	data->exit_code = 0;
	data->pid = 42;
}
