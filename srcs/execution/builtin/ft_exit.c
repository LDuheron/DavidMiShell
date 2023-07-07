/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:31:11 by svoi              #+#    #+#             */
/*   Updated: 2023/07/07 13:12:31 by sbocanci         ###   ########.fr       */
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

bool	valid_exit_number(const char *str)
{
	size_t	len;

	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isnum(str))
		return (false);
	len = ft_strlen(str);
	if (len >= 19)
		return (false);
	return (true);
}

int ft_exit(t_data *data, t_cmd_lst *cmd_lst)
{
	if (cmd_lst->cmd_node->argument[1])
	{
		if (valid_exit_number(cmd_lst->cmd_node->argument[1]))
		{
			if (cmd_lst->cmd_node->argument[2])
			{
				ft_putstr_fd("minishell: exit: too many arguments\n",
					STDERR_FILENO);
				return (1);
			}
			data->exit_return = ft_abs(ft_atoi(cmd_lst->cmd_node->argument[1]) % 256);
		}
		else
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd_lst->cmd_node->argument[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			data->exit_return = 2;
		}
	}
	rl_clear_history();
	// free_all
	/* DEBUG */
	printf("\n..ft_exit..\t exit_return:[%d]\n", data->exit_return);
	/* ***** */
	exit(data->exit_return);
}

/* Need to take care of ft_exit */
/*
void ft_exit(t_data *data, t_cmd_lst *cmd_lst)
{
	(void)data;
	(void)cmd_lst;
}

void ft_exit(t_data *data, t_cmd_lst *cmd_lst)
{
	if (cmd_lst->cmd_node->argument[1])
	{
	}

	rl_clear_history();
	// free all memory here
    exit(data->exit_return);
}
*/
