/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:08:46 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/12 18:11:09 by lduheron         ###   ########.fr       */
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

/* ..might need to control the ft_putstr_fd("exit\n") in the child !? */
int	ft_exit(t_data *data, t_cmd_lst *cmd_lst)
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
			data->exit_code = ft_abs(ft_atoi(cmd_lst->cmd_node->argument[1]) % 256);
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
	// free_all
	/* DEBUG */
	//printf("\n..ft_exit..\t exit_return:[%d]\n", data->exit_return);
	/* ***** */
	ft_putstr_fd("exit\n", 1);
	exit(data->exit_code);
}
