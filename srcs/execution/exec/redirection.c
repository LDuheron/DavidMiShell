/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:47:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/15 17:32:41 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_file_fd(enum e_type_token redir_type, char *file_name)
{
	int		file_fd;

	file_fd = -2;
	if (redir_type == SIMPLE_IN)
	{
		file_fd = open(file_name, O_RDONLY);
	}
	else if (redir_type == DOUBLE_IN)
	{
		/* DEBUG */
		//signal(SIGINT, &sigint_handler);
		/* ***** */

		ft_here_doc(file_name);

		/* DEBUG */
		//signal(SIGINT, SIG_IGN);
		/* ***** */

		file_fd = open(HD_FILE, O_RDONLY);
	}
	return (file_fd);
}

int	out_file_fd(enum e_type_token redir_type, char *file_name)
{
	int		file_fd;

	file_fd = -2;
	if (redir_type == SIMPLE_OUT)
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (redir_type == DOUBLE_OUT)
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	return (file_fd);
}

bool	set_redirection(t_data *data, t_cmd_lst *cmd_lst)
{
	t_cmd_node			*node;
	enum e_type_token	redir_type;
	int					i;

	redir_type = N_DEF;
	node = cmd_lst->cmd_node;
	i = 0;
	while (g_status < 2 && node->redir && node->redir[i])
	{
		redir_type = node->redir_type[i];
		if (redir_type == SIMPLE_IN || redir_type == DOUBLE_IN)
		{
			if (cmd_lst->in_file > 2)
				close (cmd_lst->in_file);
			cmd_lst->in_file = in_file_fd(redir_type, node->redir[i]);
		}
		if (redir_type == SIMPLE_OUT || redir_type == DOUBLE_OUT)
		{
			cmd_lst->out_file = out_file_fd(redir_type, node->redir[i]);
		}
		if (cmd_lst->in_file == -1)
		{
			ft_putstr_fd("DavidMishell: ", STDERR_FILENO);
			redir_type == DOUBLE_IN ? perror(HD_FILE) : perror(node->redir[i]);
			data->exit_code = 1;
			//g_status = 2;
			return (false);
		}
		i++;
	}
	if (g_status != 0)
		return (false);
	return (true);
}

/*
void	set_redirection(t_data *data, t_cmd_lst *cmd_lst)
{
	t_cmd_node			*node;
	enum e_type_token	redir_type;
	int					i;

	redir_type = N_DEF;
	node = cmd_lst->cmd_node;
	i = 0;
	while (g_status < 2 && node->redir && node->redir[i])
	{
		printf("\t\t\tredir @ [%p], redir[%d]: [%s]\n", node->redir, i, node->redir[i]);
		redir_type = node->redir_type[i];
		if (redir_type == SIMPLE_IN || redir_type == DOUBLE_IN)
		{
			if (cmd_lst->in_file > 2)
				close (cmd_lst->in_file);
			cmd_lst->in_file = in_file_fd(redir_type, node->redir[i]);
		}
		if (redir_type == SIMPLE_OUT || redir_type == DOUBLE_OUT)
		{
			cmd_lst->out_file = out_file_fd(redir_type, node->redir[i]);
		}
		if (cmd_lst->in_file == -1)
		{
			ft_putstr_fd("DavidMishell: ", STDERR_FILENO);
			redir_type == DOUBLE_IN ? perror(HD_FILE) : perror(node->redir[i]);
			data->exit_code = 1;
			//g_status = 2;
			break ;
		}
		i++;
	}
}
*/
