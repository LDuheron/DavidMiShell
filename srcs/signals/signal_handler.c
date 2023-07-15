/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:55:53 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/15 17:42:05 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		//printf("\nsig_handl: '%d', g_stat: '%d'\n", sig, g_status);
		if (g_status == 0)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		if (g_status == 1)
		{
			g_status = sig; // sig == 2
			close(STDIN_FILENO);
			write(1, "\n", 1);
		}
	}
}

void	ft_signal_child(int signal)
{
	if (signal == SIGINT)
	{
		exit(130);
	}
	if (signal == SIGQUIT)
	{
		exit(131);
	}
}

/*
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
void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		//printf("\nsig_handl: '%d', g_stat: '%d'\n", sig, g_status);
		if (g_status == 0)
		{
			// rl_on_new_line();
			// rl_replace_line("", 0);
			// write(1, "\n", 1);
			// rl_redisplay();
		}
		if (g_status == 1)
		{
			g_status = sig; // sig == 2
			close(STDIN_FILENO);
			write(1, "\n", 1);
		}
	}
}

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