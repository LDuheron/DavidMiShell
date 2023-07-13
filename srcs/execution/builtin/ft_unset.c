/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:46:13 by svoi              #+#    #+#             */
/*   Updated: 2023/07/13 23:48:18 by svoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_and_destroy(char **args, char **env, int index)
{
	int	i;
	int	j;
	int	k_len;

	k_len = ft_strlen(args[index]);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], args[index], k_len) == 0 && env[i][k_len] == '=')
		{
			free(env[i]);
			j = i;
			while (env[++j])
				env[j - 1] = env[j];
			env[j - 1] = NULL;
			break ;
		}
		i++;
	}
}

int	ft_unset(t_data *data, t_cmd_lst *cmd_lst)
{
	char	**argument;
	int		i;

	argument = cmd_lst->cmd_node->argument;
	i = 1;
	if (argument[i] != NULL)
	{
		while (argument[i])
		{
			search_and_destroy(argument, data->m_envp, i);
			i++;
		}
	}
	data->exit_code = 0;
	return (0);
}
