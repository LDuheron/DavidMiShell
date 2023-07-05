/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:36:46 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/04 11:17:15 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in_out(t_cmd *cmd, int *fd)
{
	//printf("child, in_file:'%d', out_file:'%d', fd[0]'%d', fd[1]:'%d'\n", cmd->in_file, cmd->out_file, fd[0], fd[1]);
	close(fd[0]);
	if (cmd->in_file >= 0)
	{
		dup2(cmd->in_file, 0);
		close(cmd->in_file);
	}
	if (cmd->out_file >= 0)
	{
		dup2(cmd->out_file, 1);
		close(cmd->out_file);
	}
	else if (cmd->next != NULL)
		dup2(fd[1], 1);
	close(fd[1]);
}

void	child_process(t_data *data, t_cmd *cmd, int *fd)
{
	redirect_in_out(cmd, fd);
	if (cmd->is_built && !cmd->spec_built)
	{
		ft_builtins(cmd, data);
		exit(data->exit_return);
	}
	ft_execve(cmd, data);
	// would need to free all the memory in child since it is duplicated 
	exit_process(data, fd);
}

void	ft_launch_cmd(t_data *data, t_cmd *cmd, int *fd)
{
	global.pid = fork();
	if (global.pid < 0)
		return ;
	else if (global.pid == 0)
	{
		if (cmd->argv[0])
			child_process(data, cmd, fd);
	}
	else
		parent_process(cmd, fd);
}

void	parent_process(t_cmd *cmd, int *fd)
{
	//printf("parent, in_file:'%d', fd[0]:'%d', fd[1]:'%d'\n", cmd->in_file, fd[0], fd[1]);
	close(fd[1]);
	if (cmd->in_file >= 0)
		close(cmd->in_file);
	if (cmd->in_file == -2)
		cmd->in_file = fd[0];
	if (cmd->next && cmd->next->in_file == -2)
		cmd->next->in_file = fd[0];
	else
		close(fd[0]);
	return ;
}

void	exit_process(t_data *data, int *fd)
{
	t_cmd	*current;

	current = data->cmdIndex->begin;
	while (current)
	{
		if (current->in_file >= 0)
			close(current->in_file);
		if (current->out_file >= 0)
			close(current->out_file);
		current = current->next;
	}
	close(fd[0]);
	close(fd[1]);
	exit(data->exit_return);
}

void	wait_all_and_finish(t_data *data, t_cmd *cmds)
{
	int	status;
	int	pid;

	while (cmds)
	{
		pid = waitpid(0, &status, 0);
		if (pid == global.pid)
		{
			if (WIFEXITED(status))
				data->exit_return = WEXITSTATUS(status);
		}
		if (cmds->out_file >= 0)
			close(cmds->out_file);
		if (cmds->in_file >= 0)
			close(cmds->in_file);
		cmds = cmds->next;
	}
}

/*
int	ft_exec(t_data *data)
{
	t_cmd_lst	*cmd;
	int			fd[2];

	//cmd = data->cmdIndex->begin;
	while (cmd)
	{
		//printf("\tnb_pipes: '%d'\n", data->cmdIndex->nb_pipe);
		if (cmd->spec_built)
			spec_built(cmd, data);
		else
		{
			if (pipe(fd) == -1)
				return (-1);
			else
				ft_launch_cmd(data, cmd, fd);
		}
		cmd = cmd->next;
	}
	wait_all_and_finish(data, data->cmdIndex->begin);
	return (1);
}
*/
