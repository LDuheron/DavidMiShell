

#include "minishell.h"

static int	ft_here_doc_init(int *file_fd)
{
	g_status = 2;
	*file_fd = open(HD_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (dup(0));
}

static void	ft_here_doc_close(int std_in_dup, int file_fd)
{
	/*
	if (g_status != 2)
		data->exit_code = 130;
	*/
	dup2(std_in_dup, STDIN_FILENO);
	close(std_in_dup);
	g_status = 0;
	close(file_fd);
}

void	ft_here_doc(char *delimiter)
{
	char	*line;
	int		file_fd;
	int		std_in_dup;

	std_in_dup = ft_here_doc_init(&file_fd);
	while (g_status == 2)
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
}
