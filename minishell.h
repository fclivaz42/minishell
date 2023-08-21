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

// --- PIPING UTILS --- //

// --- ERROR HANDLING --- //

void	error_system(int mode, char *file);
void	error_bad_format(char *src);

// --- DEBUG SWITCH --- //

# ifndef DEBUG
#  define DEBUG 0
# endif

#endif