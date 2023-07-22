/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:23:03 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/22 11:21:37 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_data *data)
{
	t_cmd_lst	*cmd_lst;

	cmd_lst = data->cmd_lst;
	while (g_status < 2 && cmd_lst)
	{
		if (cmd_lst->type == CMD_NODE && set_redirection(data, cmd_lst))
		{
			ft_launch_cmd(data, cmd_lst);
		}
		cmd_lst = cmd_lst->next;
	}
	if (g_status > 0)
		g_status = 0;
	ft_wait(data);
	signal(SIGINT, &sigint_handler);
}

/* This check handles the case if the **argumen in NULL and
there is something in **redir */
void	print_error_cmd(t_data *data, t_cmd_lst *cmd_lst)
{
	if (ft_strchr_i(cmd_lst->cmd_node->argument[0], '/') == -1)
	{
		ft_putstr_fd(cmd_lst->cmd_node->argument[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		data->exit_code = 127;
	}
	else
	{
		ft_putstr_fd("DavidMishell: ", 2);
		ft_putstr_fd(cmd_lst->cmd_node->argument[0], 2);
		if (!access(cmd_lst->cmd_node->argument[0], F_OK))
		{
			ft_putstr_fd(": Is a directory\n", 2);
			data->exit_code = 126;
		}
		else
		{
			ft_putstr_fd(": No such file or directory\n", 2);
			data->exit_code = 127;
		}
	}
	list_destroy(cmd_lst);
	if (data->m_envp)
		free_tab(data->m_envp);
	exit(data->exit_code);
}

void	print_error_dir(t_data *data, t_cmd_lst *cmd_lst)
{
	int	i;

	i = 0;
	while (cmd_lst->cmd_node->redir[i])
	{
		if (!access(cmd_lst->cmd_node->redir[i], X_OK))
		{
			ft_putstr_fd("DavidMishell: ", 2);
			ft_putstr_fd(cmd_lst->cmd_node->redir[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			break ;
		}
		i++;
	}
	data->exit_code = 127;
	list_destroy(cmd_lst);
	if (data->m_envp)
		free_tab(data->m_envp);
	exit(data->exit_code);
}

void	absolute_path_to_cmd(t_data *data, char *cmd, char to_execute[BUFFER])
{
	int		i;

	if (access(cmd, X_OK) == 0)
	{
		ft_strcpy(to_execute, cmd);
		return ;
	}
	data->path_dirs = get_path_directories(data->m_envp);
	i = 0;
	while (data->path_dirs && data->path_dirs[i])
	{
		ft_strcpy(to_execute, data->path_dirs[i]);
		ft_strcat(to_execute, "/");
		ft_strcat(to_execute, cmd);
		if (access(to_execute, X_OK) == 0)
			break ;
		i++;
	}
	if (data->path_dirs)
		free_tab(data->path_dirs);
	if (to_execute[0] == '\0')
	{
		ft_strcpy(to_execute, cmd);
	}
}

void	ft_execve(t_data *data, t_cmd_lst *cmd_lst)
{
	char	to_execute[BUFFER];
	char	**arg;

	ft_bzero(to_execute, BUFFER);
	if (cmd_lst->cmd_node->argument)
	{
		arg = cmd_lst->cmd_node->argument;
		expand_envp(data, cmd_lst->cmd_node);
		absolute_path_to_cmd(data, arg[0], to_execute);
		data->exit_code = execve(to_execute, arg, data->m_envp);
		print_error_cmd(data, cmd_lst);
	}
	else if (cmd_lst->cmd_node->redir)
	{
		print_error_dir(data, cmd_lst);
	}
}
