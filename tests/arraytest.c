/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraytest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:37:14 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/28 15:45:18 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdlib.h>

void print_array(char **arr)
{
	for (int i = 0; arr[i] != NULL; ++i)
	{
		ft_printf("Entry %d of array is %d long: %s\n", i, ft_strlen(arr[i]), arr[i]);
	}
}

int main(int ac, char *av[])
{
	if (ac < 2)
		return (1);
	char **pwd = ft_split(getenv("PWD"), '/');
	char **cdir = ft_split(av[1], '/');

	print_array(pwd);
	ft_putendl_fd("", 1);
	print_array(cdir);
}
