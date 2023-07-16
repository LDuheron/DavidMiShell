/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:31:47 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/17 00:43:13 by svoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

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
				if (check_syntax(&data->token) == SUCCESS)
					parsing(&data->cmd_lst, &data->token);
			if (data->cmd_lst)
			{
				//print_cmd_lst(&cmd_lst);
				execution(data);
			}
			list_destroy(data->cmd_lst);
			add_history(buffer);
		}
		free(buffer);
		buffer = readline("DavidMishell: ");
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
	printf("exit\n");
	return (data.exit_code);
}
