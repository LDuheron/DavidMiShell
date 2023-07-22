/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:36:46 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/22 14:07:41 by sbocanci         ###   ########.fr       */
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
	list_destroy(cmd_lst);
	if (data->m_envp)
		free_tab(data->m_envp);
	exit(data->exit_code);
}

void	redirect_in_out(t_cmd_lst *cmd_lst, int *fd)
{
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

void	child_process(t_data *data, t_cmd_lst *cmd_lst, int *fd)
{
	int	builtin;

	redirect_in_out(cmd_lst, fd);
	builtin = check_builtin(cmd_lst);
	if (builtin)
	{
		signal(SIGPIPE, SIG_IGN);
		exec_builtin_child(data, cmd_lst, builtin);
		list_destroy(cmd_lst);
		if (data->m_envp)
			free_tab(data->m_envp);
		exit(data->exit_code);
	}
	ft_execve(data, cmd_lst);
	exit_process(data, fd);
}

void	parent_process(t_cmd_lst *cmd_lst, int *fd)
{
	signal(SIGINT, SIG_IGN);
	close(fd[1]);
	if (cmd_lst->in_file >= 0)
		close(cmd_lst->in_file);
	if (cmd_lst->in_file == -2)
		cmd_lst->in_file = fd[0];
	if (cmd_lst->next && cmd_lst->next->in_file == -2)
	{
		if (cmd_lst->next->type != CMD_NODE)
			cmd_lst = cmd_lst->next;
		if (cmd_lst->next->in_file == -2)
			cmd_lst->next->in_file = fd[0];
	}
	else
		close(fd[0]);
	return ;
}

void	ft_launch_cmd(t_data *data, t_cmd_lst *cmd_lst)
{
	int	fd[2];
	int	builtin;

	builtin = check_builtin(cmd_lst);
	if (builtin && !cmd_lst->next)
	{
		exec_builtin(data, cmd_lst, builtin);
	}
	else
	{
		pipe(fd);
		data->pid = fork();
		if (data->pid < 0)
			return ;
		else if (data->pid == 0)
		{
			signal(SIGINT, &ft_signal_child);
			signal(SIGQUIT, &ft_signal_child);
			child_process(data, cmd_lst, fd);
		}
		else
			parent_process(cmd_lst, fd);
	}
}
