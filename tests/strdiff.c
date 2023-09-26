/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdiff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:44:52 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/26 16:52:47 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int main(void)
{
	char *str1 = "Hello this is Jack!";
	char *str2 = strchr(str1, 'J');

	printf("%s\n", str1);
	printf("%s\n", str2);
	printf("%ld\n", (char *)str2 - (char *)str1);
}
