/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:18:37 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/06 13:18:41 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_data *data)
{
	int			status;
	int			pid;
	t_cmd_lst	*cmd_lst;

	cmd_lst = data->cmd_lst;
	while (cmd_lst)
	{
		pid = waitpid(0, &status, 0);
		if (pid == data->pid)
		{
			if (WIFEXITED(status))
				data->exit_return = WEXITSTATUS(status);
		}
		if (cmd_lst->out_file >= 0)
			close(cmd_lst->out_file);
		if (cmd_lst->in_file >= 0)
			close(cmd_lst->in_file);
		cmd_lst = cmd_lst->next;
	}
}
