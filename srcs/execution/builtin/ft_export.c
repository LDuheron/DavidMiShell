/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:45:33 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/17 01:05:58 by svoi             ###   ########.fr       */
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

bool	ft_valid_key(char *str)
{
	int	i;

	i = 0;
	if (!is_alpha(str[i]) && str[i] != '_')
	{
		ft_putstr_fd("DavidMishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (false);
	}
	while (str[i] && str[i] != '=')
	{
		if (!(is_alpha(str[i]) || is_number(str[i])) && str[i] != '_')
		{
			ft_putstr_fd("DavidMishell: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (false);
		}
		i++;
	}
	return (true);
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
			if (ft_valid_key(argument[i]) == false)
			{
				data->exit_code = 1;
				return (1);
			}
			else
			{
				search_and_extract_key(data, argument, i);
				data->exit_code = 0;
			}
			i++;
		}
	}
	return (0);
}
