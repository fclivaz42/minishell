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
# include "libft/libft.h"

// --- STRUCTS --- //

// --- MINISHELL --- //

// --- ENV PARSING --- //

char	**ms_fullparse(char *str, char *env[]);

// --- PIPING UTILS --- //

// --- EXTRAS --- //

void	zerofree(char *s);
void	arrayfree(char **arr);

// --- ERROR HANDLING --- //

void	error_bad_format(char *src);
void	check_failed_memory(void *str);
void	error_system(int mode, char *file);

// --- DEBUG SWITCH --- //

# ifndef DEBUG
#  define DEBUG 0
# endif

#endif