/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colortest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleeper <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 03:55:19 by sleeper           #+#    #+#             */
/*   Updated: 2023/09/30 19:01:04 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#define CSET		"\033[1m\x1b[38;2;"
#define PURPL		"123;91;227m"
#define GOLD		"235;155;28m"
#define BLUE		"2;224;242m"
#define RESET		"\x1b[0m"


int main(void)
{
	printf("%s%sCOLOR TEST\n", CSET, PURPL);
	printf("%s%sCOLOR TEST\n", CSET, GOLD);
	printf("%s%sCOLOR TEST%s\n", CSET, BLUE, RESET);
	printf("WHITE AS BUCK\n");
}
