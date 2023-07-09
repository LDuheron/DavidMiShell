/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:48:26 by lduheron          #+#    #+#             */
/*   Updated: 2023/07/09 11:54:53 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_put_enum(int type)
{
	if (type == WORD)
		return ("WORD");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == SINGLE_QUOTE)
		return ("SINGLE_QUOTE");
	else if (type == DOUBLE_QUOTE)
		return ("DOUBLE_QUOTE");
	else if (type == SIMPLE_IN)
		return ("SIMPLE_IN");
	else if (type == SIMPLE_OUT)
		return ("SIMPLE_OUT");
	else if (type == DOUBLE_IN)
		return ("DOUBLE_IN");
	else if (type == DOUBLE_OUT)
		return ("DOUBLE_OUT");
	else
		return ("N_DEF");
}

void	ft_print_lst_token(t_tokens *token)
{
	t_tokens	*tmp;
	int			i;

	tmp = token;
	i = 0;
	printf("PRINT LST TOKEN\n");
	if (tmp == NULL)
	{
		printf("List is empty.\n");
		return ;
	}
	while (tmp != NULL)
	{
		printf("TOKEN NUMBER %i\n", i);
		printf("Content: %s\n", tmp->content);
		printf("Type : %i\n", tmp->type);
		printf("Len : %i\n\n", tmp->len);
		tmp = tmp->next;
		i++;
	}
}

void	print_cmd_node(t_cmd_node *cmd_node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd_node == NULL)
	{
		printf("Error: cmd_node is NULL\n");
		return ;
	}
	if (cmd_node->argument != NULL)
	{
		while (cmd_node->argument[i])
		{
			j = 0;
			printf("\t");
			printf("\tArgument[%i] : [%s]\t", i, cmd_node->argument[i]);
			while (cmd_node->arg_subst[i][j] != -2)
			{
				printf("\t");
				printf("arg_subst[%i][%i] : [%i]", i, j, cmd_node->arg_subst[i][j]);
				j++;
			}
			printf("\n");
			i++;
		}
	}
	i = 0;
	printf("\n");
	if (cmd_node->redir != NULL)
	{
		while (cmd_node->redir[i])
		{
			j = 0;
			printf("\t");
			printf("\tRedir[%i] : [%s]\t", i, cmd_node->redir[i]);
			printf("\t");
			printf("redir_type[%i] : [%i]\t", i, (cmd_node->redir_type[i]));
			while (cmd_node->redir_sub[i][j] != -2)
			{
				printf("Redirection_sub[%i][%i] : [%i]\n\n", i, j, cmd_node->redir_sub[i][j]);
				j++;
			}
			printf("\n");
			i++;
		}
	}
}

/*
void	print_cmd_node(t_cmd_node *cmd_node)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (cmd_node == NULL)
	{
		printf("Error: cmd_node is NULL\n");
		return ;
	}
	if (cmd_node->arg_subst && cmd_node->arg_subst[0])
	{
		printf("Cmd : %s\n", cmd_node->argument[0]);
		while (cmd_node->arg_subst[0][j] != -2)
		{
			printf("Cmd_subst : %i\n\n", cmd_node->arg_subst[0][j]);
			j++;
		}
	}
	if (cmd_node->argument != NULL)
	{
		while (cmd_node->argument[i])
		{
			j = 0;
			printf("Argument[%i] : %s\n", i, cmd_node->argument[i]);
			while (cmd_node->arg_subst[i][j] != -2)
			{
				printf("Cmd_subst[%i][%i] : %i\n", i, j,
					cmd_node->arg_subst[i][j]);
				j++;
			}
			i++;
		}
	}
	i = 0;
	printf("\n");
	if (cmd_node->redir != NULL)
	{
		while (cmd_node->redir[i])
		{
			j = 0;
			printf("Redirection[%i] : %s\n", i, cmd_node->redir[i]);
			printf("Redirection_type[%i] : %i\n", i,
				(cmd_node->redir_type[i]));
			while (cmd_node->redir_sub[i][j] != -2)
			{
				printf("Redirection_sub[%i][%i] : %i\n\n", i, j,
					cmd_node->redir_sub[i][j]);
				j++;
			}
			i++;
		}
	}
}
*/
void	print_cmd_lst(t_cmd_lst **cmd_lst)
{
	t_cmd_lst	*tmp;
	int			i;

	printf("\tPRINT cmd_lst : \n\n");
	tmp = *cmd_lst;
	i = 0;
	while (tmp)
	{
		printf("\t");
		printf(" ----- NODE %i ----- ", i);
		printf("\t");
		printf("type : [%s]\n", print_node_type(tmp->type));
		if (tmp->type == CMD_NODE)
			print_cmd_node(tmp->cmd_node);
		//printf("\n\n");
		if (!tmp->next)
			break ;
		i++;
		tmp = tmp->next;
	}
}
