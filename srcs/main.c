/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:31:47 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/29 18:39:06 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	prompt(char **env)
// {
// 	t_tokens	*token;
// 	t_cmd_lst	*cmd_lst;
// 	char		*buffer;
// 	int			err;
// 	int			flag;

// 	(void)env;
// 	buffer = NULL;
// 	cmd_lst = NULL;
// 	token = NULL;
// 	err = 0;
// 	flag = SUCCESS;
// 	while (!err)
// 	{
// 		if (buffer)
// 			free(buffer);
// 		buffer = readline("DavidFinshell: ");
// 		if (buffer && *buffer)
// 		{
// 			if (lexing(&token, buffer) == SUCCESS)
// 				if (check_syntax(&token) == SUCCESS)
// 					parsing(&cmd_lst, &token);
// 			if (cmd_lst)
// 				print_cmd_lst(&cmd_lst);
// 		}
// 		else
// 			break ;
// 		if (buffer && *buffer)
// 			add_history(buffer);
// 		// free_cmd_lst(&cmd_lst);
// 	}
// }

// int	main2(int argc, char **argv, char **env)
// {
// 	if (argc != 1)
// 		return (0);
// 	(void)argv;
// 	// signal(SIGINT, &sigint_handler);
// 	// signal(SIGQUIT, SIG_IGN);
// 	prompt(env);
// 	// free lst
// 	printf("exit\n");
// 	return (0);
// }

int	main(int argc, char **argv, char **env)
{
	t_tokens	*token;
	t_cmd_lst	*cmd_lst;

	(void)env;
	token = NULL;
	cmd_lst = NULL;
	if (argc != 2)
		return (0);
	if (lexing(&token, argv[1]) == SUCCESS)
		if (check_syntax(&token) == SUCCESS)
			parsing(&cmd_lst, &token);
	// if (cmd_lst)
	// 	print_cmd_lst(&cmd_lst);
	free_cmd_lst(&cmd_lst);
	return (0);
}
