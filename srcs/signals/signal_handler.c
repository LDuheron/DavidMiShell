/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:55:53 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/18 14:42:43 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_status != 1 && g_status != 2)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_status = 3;
		}
		if (g_status == 1)
		{
			g_status = sig;
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
