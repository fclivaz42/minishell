/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colortest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleeper <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 03:55:19 by sleeper           #+#    #+#             */
/*   Updated: 2023/09/30 04:28:26 by sleeper          ###   LAUSANNE.CH       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#define PURPL "\x1b[38;2;123;91;227m\033[1m"
#define RESET "\x1b[0m"

int main(void)
{
	printf("%sCOLOR TEST\n", PURPL);
	printf("%sCOLOR TEST\n", RESET);
}
