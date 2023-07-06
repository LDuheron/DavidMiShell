/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:31:11 by svoi              #+#    #+#             */
/*   Updated: 2023/07/07 00:29:06 by svoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isnum(char *str)
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

int ft_exit(t_data *data, t_cmd_lst *cmd_lst)
{
	int	code;

	code = 0;
	if (!cmd_lst->cmd_node)
	{
		// free all memory
		exit(data->exit_return);
		return (0);
	}
	else if (cmd_lst->cmd_node->argument[1] 
		&& !ft_isnum(cmd_lst->cmd_node->argument[1]))
	{
		ft_putstr_fd("davidMishell: exit: ", 2);
		ft_putstr_fd(cmd_lst->cmd_node->argument[1], 2);
		ft_putstr_fd(" numeric argument required\n", 2);
		// free all memory
		exit(2);
		return (0);
	}
	else if (cmd_lst->cmd_node->argument[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		data->exit_return = 1;
		return (1);
	}
	else if (cmd_lst->cmd_node->argument[1])
		code = ft_abs(ft_atoi(cmd_lst->cmd_node->argument[1]) % 256);
	// free all memory
	exit(code);
	return (0);
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
