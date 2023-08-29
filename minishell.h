/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:27:13 by fclivaz           #+#    #+#             */
/*   Updated: 2023/08/21 18:27:29 by fclivaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// --- INCLUDES --- //

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

// --- STRUCTS --- //

// --- MINISHELL --- //

char	*readline_proompter(char *env[]);
void	execute(char **commands, char *env[]);

// --- ENV PARSING --- //

char	**ms_fullparse(char *str);
t_list	*append_argument(t_list *list, char *str);
void	do_the_rest(t_list *list, char *str);

// --- PIPING UTILS --- //

// --- EXTRAS --- //

void	zerofree(char *s);
void	arrayfree(char **arr);

// --- ERROR HANDLING --- //

void	error_bad_format(char *src);
void	check_failed_memory(void *str);
void	error_system(int mode, char *file);

// --- DEBUG SWITCHES --- //

# ifndef DEBUG
#  define DEBUG 0
# endif
# define HOSTNAME "HOSTNAME"
# ifdef WSL2
#  undef HOSTNAME
#  define HOSTNAME "NAME"
# endif


#endif