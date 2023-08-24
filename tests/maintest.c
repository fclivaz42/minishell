/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:44:42 by fclivaz           #+#    #+#             */
/*   Updated: 2023/08/24 16:44:49 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	zerofree(char *s)
{
	ft_bzero(s, ft_strlen(s));
	free(s);
}

void	arrayfree(char **arr)
{
	int		x;

	x = -1;
	while (arr[++x] != NULL)
		zerofree(arr[x]);
	free(arr);
}

int	main(int ac, char *av[], char *env[])
{
	int		x = -1;
	char	**commands;
//	char	*str = (char *)ft_calloc(32, sizeof(char));

//	fgets(str, 31, stdin);
	commands = ms_fullparse(av[1], env);
	while (commands[++x] != NULL)
		printf("command %d is: %s\n", x, commands[x]);
	arrayfree(commands);
	return (0);
}