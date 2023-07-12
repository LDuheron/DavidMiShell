/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:31:47 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/12 11:07:06 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// MAIN WITHOUT READLINE
// int	main_2(int argc, char **argv, char **env)
// {
// 	t_tokens	*token;
// 	t_cmd_lst	*cmd_lst;

// 	(void)env;
// 	token = NULL;
// 	cmd_lst = NULL;
// 	if (argc != 2)
// 		return (0);
// 	if (lexing(&token, argv[1]) == SUCCESS)
// 		if (check_syntax(&token) == SUCCESS)
// 			parsing(&cmd_lst, &token);
// 	return (0);
// }

void	prompt(t_data *data)
{
	t_tokens	*token;
	t_cmd_lst	*cmd_lst;
	char		*buffer;
	int			err;
	//int			flag;

	buffer = NULL;
	cmd_lst = NULL;
	token = NULL;
	err = 0;
	//flag = SUCCESS;
	while (!err)
	{
		buffer = readline("DavidMishell: ");
		if (!buffer)
			break ;
		else if (empty_buffer(buffer))
			continue ;
		else
		{
			if (lexing(&token, buffer) == SUCCESS)
				if (check_syntax(&token) == SUCCESS)
					parsing(&cmd_lst, &token);
			if (cmd_lst)
			{
				data->cmd_lst = cmd_lst;
				print_cmd_lst(&cmd_lst);
				execution(data);
			}
			list_destroy(cmd_lst);
			cmd_lst = NULL;
		}
		add_history(buffer);
		free(buffer);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	(void)argv;
	
	if (argc != 1)
		return (0);
	init_data(&data, env);

	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	prompt(&data);
	free_tab(data.m_envp);
	printf("exit\n");
	return (0);
}
