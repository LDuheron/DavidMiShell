/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:55:53 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/13 09:08:17 by svoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		//printf("\tsig_handl: '%d', pid: '%d'", sig, global.pid);
		if (g_status == 0)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		if (g_status == 2)
		{
			//g_status = 0;
			close(STDIN_FILENO);
		}
	}
}

/*
void	sigint_handler(int sig)
{
	(void)sig;
	//printf("\tsig_handl: '%d', pid: '%d'", sig, global.pid);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		close(STDIN_FILENO);
		//g_signal = 1;
	}
}
*/