/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:36:46 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/06 19:35:58 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_process(t_data *data, int *fd)
{
	t_cmd_lst	*cmd_lst;

	cmd_lst = data->cmd_lst;
	while (cmd_lst)
	{
		if (cmd_lst->in_file >= 0)
			close(cmd_lst->in_file);
		if (cmd_lst->out_file >= 0)
			close(cmd_lst->out_file);
		cmd_lst = cmd_lst->next;
	}
	close(fd[0]);
	close(fd[1]);

	/* DEBUG */
	/* ***** */
	exit(data->exit_return);
}

void	redirect_in_out(t_cmd_lst *cmd_lst, int *fd)
{
	//printf("child, in_file:'%d', out_file:'%d', fd[0]'%d', fd[1]:'%d'\n", cmd_lst->in_file, cmd_lst->out_file, fd[0], fd[1]);
	close(fd[0]);
	if (cmd_lst->in_file >= 0)
	{
		dup2(cmd_lst->in_file, 0);
		close(cmd_lst->in_file);
	}
	if (cmd_lst->out_file >= 0)
	{
		dup2(cmd_lst->out_file, 1);
		close(cmd_lst->out_file);
	}
	else if (cmd_lst->next != NULL)
		dup2(fd[1], 1);
	close(fd[1]);
}

/* Need to take care of ft_execve() */
void	child_process(t_data *data, t_cmd_lst *cmd_lst, int *fd)
{
	int	builtin;

	redirect_in_out(cmd_lst, fd);

	builtin = check_builtin(cmd_lst);

	//if (cmd_lst->is_built && !cmd_lst->spec_built)

	if (builtin)
	{
		exec_builtin(data, cmd_lst, builtin);
		//ft_builtins(cmd, data);
		exit(data->exit_return);
	}
	ft_execve(data, cmd_lst);
	// ?? would need to free all the memory in child since it is duplicated ??
	exit_process(data, fd);
}

void	parent_process(t_cmd_lst *cmd_lst, int *fd)
{
	//printf("parent, in_file:'%d', fd[0]:'%d', fd[1]:'%d'\n", cmd_lst->in_file, fd[0], fd[1]);
	close(fd[1]);
	if (cmd_lst->in_file >= 0)
		close(cmd_lst->in_file);
	if (cmd_lst->in_file == -2)
		cmd_lst->in_file = fd[0];
	if (cmd_lst->next && cmd_lst->next->in_file == -2)
		cmd_lst->next->in_file = fd[0];
	else
		close(fd[0]);
	return ;
}

void	ft_launch_cmd(t_data *data, t_cmd_lst *cmd_lst, int *fd)
{
	// fork() need to be called in separate functoin with proper error handling
	printf("\t..pipe & fork");
	printf("\t..ft_launch_cmd..\n");

	data->pid = fork();
	if (data->pid < 0)
		return ;
	else if (data->pid == 0)
	{
		if (cmd_lst->cmd_node->argument[0])
			child_process(data, cmd_lst, fd);
	}
	else
		parent_process(cmd_lst, fd);
}
