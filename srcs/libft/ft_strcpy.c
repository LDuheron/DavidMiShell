/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:11:15 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/17 11:52:43 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (src[size] != '\0')
		size++;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	while (i <= size)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
