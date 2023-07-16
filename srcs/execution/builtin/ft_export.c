/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:45:33 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/16 17:25:51 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_envp(char **m_envp)
{
	int	i;

	i = 0;
	while (m_envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(m_envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

/* 
** The following errors are generated in bash if input (export =)
	or (export FT_USER+) :

bash: export: `FT_USER+': not a valid identifier
bash: export: `=': not a valid identifier

** this is not handled here.. not sure if it is needed ?!
*/

void	search_and_extract_key(t_data *data, char **argument, int index)
{
	char	*key;
	char	*tmp;
	int		i;

	i = ft_strchr_i(argument[index], '=');
	if (++i > 0)
	{
		key = ft_substr(argument[index], 0, i);
		if (argument[index][i - 2] == '+')
		{
			free(key);
			tmp = ft_substr(argument[index], 0, i - 2);
			key = ft_strjoin(tmp, "=");
			add_envp_variable(data, key, argument[index] + i, true);
			free(tmp);
		}
		else if (ft_strlen(key) > 1)
			add_envp_variable(data, key, argument[index] + i, false);
		free(key);
	}
}

int	ft_export(t_data *data, t_cmd_lst *cmd_lst)
{
	char	**argument;
	int		i;

	if (cmd_lst->cmd_node->argument[1] == NULL)
		put_envp(data->m_envp);
	else
	{
		i = 1;
		argument = cmd_lst->cmd_node->argument;
		while (argument[i])
		{
			search_and_extract_key(data, argument, i);
			i++;
		}
	}
	data->exit_code = 0;
	return (0);
}
