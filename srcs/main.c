/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:31:47 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/21 19:05:31 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	g_status_update(t_data *data)
{
	if (g_status)
	{
		g_status = 0;
		data->exit_code = 130;
	}
}

void	prompt(t_data *data)
{
	char		*buffer;

	buffer = readline("DavidMishell: ");
	while (buffer)
	{
		data->cmd_lst = NULL;
		if (!empty_buffer(buffer))
		{
			if (lexing(&data->token, buffer) == SUCCESS)
				if (check_syntax(data, &data->token) == SUCCESS)
					parsing(&data->cmd_lst, &data->token);
			if (data->cmd_lst)
				execution(data);
			if (data->cmd_lst)
				list_destroy(data->cmd_lst);
			add_history(buffer);
		}
		free(buffer);
		buffer = readline("DavidMishell: ");
		g_status_update(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data		data;

	(void)argv;
	if (argc != 1)
		return (0);
	init_data(&data, env);
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	prompt(&data);
	if (data.m_envp)
		free_tab(data.m_envp);
	ft_putendl_fd("exit", 1);
	return (data.exit_code);
}
