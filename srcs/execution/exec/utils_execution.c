/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:18:37 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/22 13:45:32 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	last_pid(t_data *data, int status)
{
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		data->exit_code = WTERMSIG(status) + 128;
		if (data->exit_code == 130)
			ft_putstr_fd("\n", STDERR_FILENO);
		if (data->exit_code == 131)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
}

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
			last_pid(data, status);
		if (cmd_lst->out_file >= 0)
			close(cmd_lst->out_file);
		if (cmd_lst->in_file >= 0)
			close(cmd_lst->in_file);
		cmd_lst = cmd_lst->next;
	}
	unlink(HD_FILE);
}

void	builtin_redirect_in_out(t_cmd_lst *cmd_lst, int *in, int *out)
{
	if (cmd_lst->in_file >= 0)
	{
		*in = dup(STDIN_FILENO);
		dup2(cmd_lst->in_file, STDIN_FILENO);
	}
	if (cmd_lst->out_file >= 0)
	{
		*out = dup(STDOUT_FILENO);
		dup2(cmd_lst->out_file, STDOUT_FILENO);
	}
}

void	builtin_close_in_out_files(t_cmd_lst *cmd_lst, int *in, int *out)
{
	if (cmd_lst->in_file >= 0)
	{
		dup2(*in, STDIN_FILENO);
		close(*in);
		close(cmd_lst->in_file);
	}
	if (cmd_lst->out_file >= 0)
	{
		dup2(*out, STDOUT_FILENO);
		close(*out);
		close(cmd_lst->out_file);
	}
}
