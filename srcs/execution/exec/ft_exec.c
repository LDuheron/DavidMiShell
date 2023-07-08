/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:36:46 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/08 20:29:09 by sbocanci         ###   ########.fr       */
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
	/* DEBUG */
	//printf("..redir_in_out.. in_file:'%d', out_file:'%d', fd[0]'%d', fd[1]:'%d'\t", cmd_lst->in_file, cmd_lst->out_file, fd[0], fd[1]);
	/* ***** */

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

/* Would need to change the logic of executing builtin commands
** if there is no pipe before or after current node exec_builtin() directly in the parent 
** otherwise exec_builtin() in the child process 
void	child_process(t_data *data, t_cmd_lst *cmd_lst, int *fd)
{
	int	builtin;

	redirect_in_out(cmd_lst, fd);
	builtin = check_builtin(cmd_lst);
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
** another version of child_process() right bellow */

void	child_process(t_data *data, t_cmd_lst *cmd_lst, int *fd)
{
	int	builtin;

	/* DEBUG */
	printf("\t\t..child_process..");
	/* ***** */

	redirect_in_out(cmd_lst, fd);

	builtin = check_builtin(cmd_lst);

	/* DEBUG */
	printf("\tbuiltin: [%s], argument_0:[%s]", print_builtin(builtin), cmd_lst->cmd_node->argument[0]);
	printf("\n");
	/* ***** */

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

/* This function designed to handle piping in the case where each node 
** represents commands separated by the pipe |
** would need to change it to reflect the way data is stored DavidMishell..
** each node can have either CMD_NODE or PIPE types.
void	parent_process(t_cmd_lst *cmd_lst, int *fd)
{
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
** new version of the parent_process f() is bellow */

void	parent_process(t_cmd_lst *cmd_lst, int *fd)
{
	/* DEBUG 
	t_cmd_lst *tmp = cmd_lst;
	printf("\t\t..parent_process..");
	printf(".. in_file:[%d], out_file:[%d], fd[0]:[%d], fd[1]:[%d]\t", cmd_lst->in_file, cmd_lst->out_file, fd[0], fd[1]);
	printf("nodes_type:\n");
	while (tmp)
	{
		printf("\t\t\ttype:[%s]\t", print_node_type(tmp->type));
		if (tmp->cmd_node)
			printf("cmd:[%s]", tmp->cmd_node->argument[0]);
		printf("\n");
		tmp = tmp->next;
	}
	//printf("\n");
	*/
	/* ***** */
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

	/* DEBUG */
	printf("\t..ft_launch_cmd..");
	printf("\tbuiltin: [%s], argument_0:[%s]\t", print_builtin(builtin), cmd_lst->cmd_node->argument[0]);
	printf("cmd_lst->next @ [%p]", cmd_lst->next);
	printf("\n");
	/* ***** */

	if (builtin && !cmd_lst->next)
	{
		printf("\t\t.... exec_builtin\n");
		exec_builtin(data, cmd_lst, builtin);
	}
	else
	{
		printf("\t\t.... pipe & fork\n");
		// both pipe() and fork() need to be called in separate functoin with proper error handling
		if (pipe(fd) == -1)
			printf("Pipe error handling here\n");
		data->pid = fork();
		if (data->pid < 0)
			return ;
		else if (data->pid == 0)
		{
			child_process(data, cmd_lst, fd);
		}
		else
		{
			parent_process(cmd_lst, fd);
		}
	}
}

/*
void	ft_launch_cmd(t_data *data, t_cmd_lst *cmd_lst, int *fd)
{
	// fork() need to be called in separate functoin with proper error handling
	printf("\t\t..pipe & fork\n");
	//printf("\t..ft_launch_cmd..\n");

	data->pid = fork();
	if (data->pid < 0)
		return ;
	else if (data->pid == 0)
	{
		child_process(data, cmd_lst, fd);
		//if (cmd_lst->cmd_node->argument[0])
	}
	else
		parent_process(cmd_lst, fd);
}
*/
