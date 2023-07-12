/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:47:52 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/12 18:15:40 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	ft_close_heredoc()
{
	close(fd);
	dup2(fd_cpy, STDIN_FILENO);
	close(fd_cpy);
}

int	ft_create_here_doc(char *delimiter)
{
	int		fd[2];
	int		fd_cpy;
	int		file_fd;
	char	*buffer;

	dup(STDIN_FILENO);
	if (pipe(fd) == -1)
	{
		// pipe error handling here
		return (errno);
	}
	signal(SIGINT, &ft_signal_heredoc);
	buffer = NULL;
	file_fd = open(HD_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(1, "> ", 2);
	while (get_next_line(0, &buffer) > 0)
	{
		if (!ft_strncmp(buffer, delimiter, ft_strlen(buffer)))
			break ;
		else
		{
			ft_putstr_fd(buffer, fd);
			write(fd, "\n", 1);
		}
		free(buffer);
		write(1, "> ", 2);
	}
	free(buffer);
	close (file_fd);
	return (0);
}
*/

void	ft_create_here_doc(char *delimiter)
{
	int		fd;
	char	*buffer;

	signal(SIGINT, &ft_signal_heredoc);
	buffer = NULL;
	fd = open(HD_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(1, "> ", 2);
	while (get_next_line(0, &buffer) > 0)
	{
		/* we need to handle the case of ctrl^C / ctrl^D !?.. */
		if (!ft_strncmp(buffer, delimiter, ft_strlen(buffer)))
			break ;
		else
		{
			ft_putstr_fd(buffer, fd);
			write(fd, "\n", 1);
		}
		free(buffer);
		write(1, "> ", 2);
	}
	free(buffer);
	close (fd);
}

int	in_file_fd(enum e_type_token redir_type, char *file_name)
{
	int		file_fd;

	file_fd = -2;
	if (redir_type == SIMPLE_IN)
	{
		file_fd = open(file_name, O_RDONLY);
		if (file_fd < 0)
		{
			ft_putstr_fd("DavidMishell: ", STDERR_FILENO);
			perror(file_name);
		}
	}
	else if (redir_type == DOUBLE_IN)
	{
		ft_create_here_doc(file_name);
		file_fd = open(HD_FILE, O_RDONLY);
		if (file_fd < 0)
		{
			ft_putstr_fd("DavidMishell: ", STDERR_FILENO);
			perror(HD_FILE);
		}
	}
	return (file_fd);
}

int	out_file_fd(enum e_type_token redir_type, char *file_name)
{
	int		file_fd;

	file_fd = -2;
	if (redir_type == SIMPLE_OUT)
	{
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (file_fd < 0)
		{
			ft_putstr_fd("DavidMishell: ", STDERR_FILENO);
			perror(file_name);
		}
	}
	else if (redir_type == DOUBLE_OUT)
	{
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (file_fd < 0)
		{
			ft_putstr_fd("DavidMishell: ", STDERR_FILENO);
			perror(file_name);
		}
	}
	return (file_fd);
}

void	set_redirection(t_data *data, t_cmd_lst *cmd_lst)
{
	t_cmd_node			*node;
	enum e_type_token	redir_type;
	int					i;

	(void)data;
	redir_type = N_DEF;
	node = cmd_lst->cmd_node;
	i = 0;
	if (cmd_lst->cmd_node->redir)
	{
		while (node->redir[i])
		{
			redir_type = node->redir_type[i];
			if (redir_type == SIMPLE_IN || redir_type == DOUBLE_IN)
			{
				cmd_lst->in_file = in_file_fd(redir_type, node->redir[i]);
			}
			if (redir_type == SIMPLE_OUT || redir_type == DOUBLE_OUT)
			{
				cmd_lst->out_file = out_file_fd(redir_type, node->redir[i]);
			}
			i++;
		}
	}
}
