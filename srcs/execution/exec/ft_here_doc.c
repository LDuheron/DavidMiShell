/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:18:19 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/13 16:18:23 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_here_doc_init(int *file_fd)
{
	g_status = 1;
	*file_fd = open(HD_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (dup(STDIN_FILENO));
}

static void	ft_here_doc_close(int std_in_dup, int file_fd)
{
	dup2(std_in_dup, STDIN_FILENO);
	close(std_in_dup);
	close(file_fd);
}

void	ft_here_doc(char *delimiter)
{
	char	*line;
	int		file_fd;
	int		std_in_dup;

	std_in_dup = ft_here_doc_init(&file_fd);
	/* DEBUG 
	printf("\t\t\t..START..ft_heredoc..\t");
	printf("g_status: [%d]\n", g_status);
	*/
	/* **** */
	while (g_status == 1)
	{
		line = readline("> ");
		if (line)
		{
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break ;
			}
			write(file_fd, line, ft_strlen(line));
			write(file_fd, "\n", 1);
			free(line);
		}
		else
			break ;
	}
	ft_here_doc_close(std_in_dup, file_fd);
	/* DEBUG 
	printf("\t\t\t..END..ft_heredoc..\t");
	printf("g_status: [%d]\n", g_status);
	*/
	/* **** */
}
