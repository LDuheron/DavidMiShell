/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:31:47 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/28 09:58:43 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// || flag != SUCCESS
void	prompt(char **env)
{
	t_tokens	*token;
	t_cmd_lst	*cmd_lst;
	char		*buffer;
	int			err;
	int			flag;

	(void)env;
	buffer = NULL;
	cmd_lst = NULL;
	token = NULL;
	err = 0;
	flag = SUCCESS;
	while (!err)
	{
		if (buffer)
			free(buffer);
		buffer = readline("DavidFinshell: ");
		if (buffer && *buffer)
		{
			if (lexing(&token, buffer) == SUCCESS)
				if (check_syntax(&token) == SUCCESS)
					parsing(&cmd_lst, &token);
			if (cmd_lst)
				print_cmd_lst(&cmd_lst);
		}
		if (buffer && *buffer)
			add_history(buffer);
		free_cmd_lst(&cmd_lst);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_tokens	*token;
	t_cmd_lst	*cmd_lst;

	cmd_lst = NULL;
	token = NULL;
	(void)env;
	if (argc != 1)
		return (0);
	// (void)argv;
	// prompt(env);
	if (lexing(&token, argv[1]) == SUCCESS)
			if (check_syntax(&token) == SUCCESS)
				parsing(&cmd_lst, &token);
	if (cmd_lst)
		print_cmd_lst(&cmd_lst);
	free_cmd_lst(&cmd_lst);
	return (0);
}
