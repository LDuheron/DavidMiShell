/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:47:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/16 19:56:28 by svoi             ###   ########.fr       */
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
		ft_here_doc(file_name);
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

bool	ft_infile_error(t_data *data, int redir_type, char *in_file)
{
	if (redir_type == DOUBLE_IN)
	{
		ft_putstr_fd("DavidMishell: ", STDERR_FILENO);
		perror(HD_FILE);
	}
	else
	{
		ft_putstr_fd("DavidMishell: ", STDERR_FILENO);
		perror(in_file);
	}
	data->exit_code = 1;
	return (false);
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
			cmd_lst->out_file = out_file_fd(redir_type, node->redir[i]);
		if (cmd_lst->in_file == -1)
			return (ft_infile_error(data, redir_type, node->redir[i]));
		i++;
	}
	if (g_status != 0)
		return (false);
	return (true);
}
