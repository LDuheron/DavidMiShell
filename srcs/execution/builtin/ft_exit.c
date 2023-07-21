/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:45:35 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/21 15:46:29 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isnum(const char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (false);
		str++;
	}
	return (true);
}

int	ft_abs(int num)
{
	if (num < 0)
		return (num * -1);
	return (num);
}

bool	valid_exit_number(char *str)
{
	size_t	len;
	int		neg;

	neg = 0;
	if (*str == '-')
		neg = 1;
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isnum(str))
		return (false);
	len = ft_strlen(str);
	if (len > 19)
		return (false);
	else if (len == 19)
	{
		if ((neg && ft_strcmp(LONG_MIN_STR, str) < 0)
			|| (!neg && ft_strcmp(LONG_MAX_STR, str) < 0))
			return (false);
	}
	return (true);
}

int	ft_exit(t_data *data, t_cmd_lst *cmd_lst)
{
	if (cmd_lst->cmd_node->argument[1])
	{
		if (valid_exit_number(cmd_lst->cmd_node->argument[1]))
		{
			if (cmd_lst->cmd_node->argument[2])
			{
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				data->exit_code = 1;
				return (1);
			}
			data->exit_code = ft_atolong(cmd_lst->cmd_node->argument[1]) % 256;
		}
		else
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd_lst->cmd_node->argument[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			data->exit_code = 2;
		}
	}
	rl_clear_history();
	list_destroy(data->cmd_lst);
	free_tab(data->m_envp);
	ft_putstr_fd("exit\n", 1);
	exit(data->exit_code);
}
