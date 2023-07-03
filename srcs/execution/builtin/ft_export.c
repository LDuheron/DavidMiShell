/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:45:33 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/03 15:42:42 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_envp(char **m_envp)
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
** The following errors are generated in bash if input (export =) or (export FT_USER+) :

bash: export: `FT_USER+': not a valid identifier
bash: export: `=': not a valid identifier

** this is not handled here.. not sure if it is needed ?!
**
** Also multiple arguments to export are not handled, only the first is processed.. ?!
eg: export VAR=value VAR2=value2
int ft_export(t_cmd *cmd, t_data *data)
{
	char	*key;
	char	*tmp;
	int		i;

	if (cmd->argv[1] == NULL)
		put_envp(data->m_envp);
	i = search_egal(cmd->argv[1]);
	if (++i > 0)
	{
		key = ft_substr(cmd->argv[1], 0, i);
		if (cmd->argv[1][i - 2] == '+')
		{
			free(key);
			tmp = ft_substr(cmd->argv[1], 0, i - 2);
			key = ft_strjoin(tmp, "=");
			add_envp_variable(data, key, cmd->argv[1] + i, true);
			free(tmp);
		}
		else if (ft_strlen(key) > 1)
			add_envp_variable(data, key, cmd->argv[1] + i, false);
		free(key);
	}
	data->exit_return = 0;
	return (0);
}

*/