/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:07:17 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/03 19:45:11 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_data *data)
{
	//(void)data;
	t_cmd_lst *cmd;
	
	//check_builtin_first(data);
	cmd = data->cmd_lst;
	if (cmd->type == CMD_NODE)	
	{
		//ft_exec(data);
	}
}
