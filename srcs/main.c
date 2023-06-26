/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:31:47 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/22 17:57:34 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *read_line(char *buffer)
// {
// 	if (!line)
// 		break ;
// 	buffer = readline("DavidFinshell: ");
// 	if (buffer && *buffer)
// 			add_history(buffer);
// 	return ()
// }

// void	prompt(char **env)
// {
// 	t_tokens	*token;
// 	t_cmd_lst	*cmd_lst;
// 	char		*buffer;
// 	int			err;

// 	(void)env;
// 	token = NULL;
// 	cmd_lst = NULL;
// 	err = 0;
// 	while (!err)
// 	{
// 		if (!buffer)
// 			break ;
// 		lexing(&token, buffer);
// 		// ft_print_lst_token(token);
// 		check_syntax(&token);
// 		parsing(&cmd_lst, &token);
// 		print_cmd_lst(&cmd_lst);
// 		if (buffer && *buffer)
// 			add_history(buffer);
// 		free(buffer);
// 	}
// }

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
	}
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 1)
		return (0);
	(void)argv;
	prompt(env);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_tokens	*token;
// 	t_cmd_lst	*cmd_lst;
// 	int			flag;

// 	if (argc != 2)
// 		return (0);
// 	token = NULL;
// 	cmd_lst = NULL;
// 	lexing(&token, argv[1]);
// 	// ft_print_lst_token(token);
// 	check_syntax(&token);
// 	flag = parsing(&cmd_lst, &token);
// 	printf("flag : %i\n", flag);
// 	// print_cmd_lst(&cmd_lst);
// 	return (0);
// }

// free_cmd_lst(&cmd_lst);
// free(cmd_lst);
// dollar entre simple quote = pas de subst sauf si
//  simple quote dans double quote.
