/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <fclivaz@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 04:18:54 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/05 04:36:20 by fclivaz          ###   LAUSANNE.CH       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	validator(char *rl)
{
	char	c;
	char	*str;

	if (ft_strlen(rl) == 0)
		return (1);
	str = rl;
	while (*rl)
	{
		if (ft_strchr("<>:&{}*^[]()\\;%~`?!#", *rl))
			return (!error_unsupported_character(*rl));
		if (*rl == 34 || *rl == 39)
		{
			c = *rl;
			++rl;
			while (!(*rl == c || *rl == 0))
				++rl;
			if (*rl == 0)
				return (!error_bad_format(str));
		}
		++rl;
	}
	return (0);
}

int main(void)
{
	char *rl;

	while (1)
	{
		rl = memchk(readline("balls>"));
		if (!validator(rl))
		{
			add_history(rl);
			printf("%s\n", rl);
		}
		free(rl);
	}
}
