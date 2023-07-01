/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection_save.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:23:41 by lduheron          #+#    #+#             */
/*   Updated: 2023/06/30 15:23:52 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int	is_redirection_2(t_data_lexing *data_lexing)
// {
// 	char	*string;
// 	int		type;

// 	string = malloc(sizeof(char) * 3);
// 	if (!string)
// 		return (ERROR_MALLOC);
// 	if ((*data_lexing).line[(*data_lexing).pos])
// 		string[0] = (*data_lexing).line[(*data_lexing).pos];
// 	else
// 		string[0] = '\0';
// 	if ((*data_lexing).line[(*data_lexing).pos + 1])
// 		string[1] = (*data_lexing).line[(*data_lexing).pos + 1];
// 	else
// 		string[1] = '\0';
// 	string[2] = '\0';
// 	if (ft_strncmp(string, "<<", 2) == 0)
// 		type = DOUBLE_IN;
// 	else if (ft_strncmp(string, ">>", 2) == 0)
// 		type = DOUBLE_OUT;
// 	else if (ft_strncmp(string, "<", 1) == 0)
// 		type = SIMPLE_IN;
// 	else if (ft_strncmp(string, ">", 1) == 0)
// 		type = SIMPLE_OUT;
// 	else
// 		type = N_DEF;
// 	free (string);
// 	return (type);
// }
