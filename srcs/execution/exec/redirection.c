/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:47:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/11 15:55:23 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_in_file_fd(char *file_name)
{
	int		file_fd;

	file_fd = open(file_name, O_RDONLY);
	if (file_fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(file_name);
		return (-1);
	}
	return (file_fd);
}

int	get_here_doc_fd(char *heredoc_str)
{
	printf("\t\t..heredoc_string: [%s]\n", heredoc_str);
	return (-2);
}

int	get_out_file_fd(char *file_name)
{
	int		file_fd;

	file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file_fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(file_name);
		return (-1);
	}
	return (file_fd);
}
int	get_append_file_fd(char *file_name)
{
	int		file_fd;

	file_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (file_fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(file_name);
		return (-1);
	}
	return (file_fd);
}

void	set_redirection(t_data *data, t_cmd_lst *cmd_lst)
{
	(void)data;
	t_cmd_node	*node;
	int			i;
	printf("\t..set_redirection..\n");

	i = 0;
	node = cmd_lst->cmd_node;
	if (node->redir)
	{
		while (node->redir[i])
		{
			if (node->redir_type[i] == SIMPLE_IN)
			{
				cmd_lst->in_file = get_in_file_fd(node->redir[i]);
			}
			if (node->redir_type[i] == DOUBLE_IN)
			{
				cmd_lst->in_file = get_here_doc_fd(node->redir[i]);
			}
			if (node->redir_type[i] == SIMPLE_OUT)
			{
				cmd_lst->out_file = get_out_file_fd(node->redir[i]);
			}
			if (node->redir_type[i] == DOUBLE_OUT)
			{
				cmd_lst->out_file = get_append_file_fd(node->redir[i]);
			}
			i++;
		}
	}
}
