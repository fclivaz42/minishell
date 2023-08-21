/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:58:24 by fclivaz           #+#    #+#             */
/*   Updated: 2023/08/21 18:58:33 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void zerofree(char *s)
{
	int		x;

	x = -1;
	while (s[++x] != NULL)
		s[x] = 0;
	free(str);
}

void arrayfree(void **arr)
{
	int		x;

	x = -1;
	while (arr[++x] != NULL)
		zerofree(arr[x]);
}

int main (int argc, char *argv[], char *env[])
{
	// bonsoir :)
}