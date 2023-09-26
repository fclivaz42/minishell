/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirtest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:39:51 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/26 19:27:55 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>

void stuff(void)
{
	int fd = open("../../", O_RDONLY);
	printf("in this thOng we open with fd %d\n", fd);
}


int main(void)
{
	stuff();
	int fd = open("./", O_RDONLY);
	int fd2 = open("../../../", O_RDONLY);
	if (fd > 0)
		printf("opened directory with fd %d\n", fd);
	if (fd2 > 0)
		printf("opened directory 2 with fd %d\n", fd2);
}
