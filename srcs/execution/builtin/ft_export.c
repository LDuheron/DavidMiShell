/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:45:33 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/19 12:39:15 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_envp(char *str)
{
	int	i;

	ft_putstr_fd("declare -x ", 1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
	if (str[i])
	{
		ft_putstr_fd("=\"", 1);
		while (str[++i])
			ft_putchar_fd(str[i], 1);
		ft_putchar_fd('"', 1);
	}
	ft_putstr_fd("\n", 1);
}

static void	sort_envp(char **m_envp)
{
	char	*tmp;
	int		i;
	int		j;
	int		n;

	n = 0;
	while (m_envp[n])
		n++;
	i = -1;
	while (++i < n - 1)
	{
		j = -1;
		while (++j < n - i - 1)
		{
			if (ft_strcmp(m_envp[j], m_envp[j + 1]) > 0)
			{
				tmp = m_envp[j];
				m_envp[j] = m_envp[j + 1];
				m_envp[j + 1] = tmp;
			}
		}
	}
	n = -1;
	while (m_envp[++n])
		put_envp(m_envp[n]);
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
	else
		add_envp_variable(data, argument[index], "", false);
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
		if (!(is_alpha(str[i]) || is_number(str[i])
				|| (str[i] == '+' && str[i + 1] == '='))
			&& str[i] != '_')
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
		sort_envp(data->m_envp);
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
