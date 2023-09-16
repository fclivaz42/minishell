/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:27:13 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/16 18:01:47 by fclivaz          ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include "libft/libft.h"

// --- STRUCTS --- //

typedef struct t_minishell
{
	t_list  *env;
	t_list  *commands;
	char	*pwd;
	pid_t	pid;
}	t_minishell;


typedef struct t_token
{
	t_list		*word;
	int		fd_in;
	int		fd_out;
	struct t_token	*next;
	struct t_token	*prev;
}	t_token;

// --- MINISHELL --- //

t_list	*ms_fullparse(char *str, t_list *env);
char	*readline_proompter(t_list *env);
char	*interpreter(char *raw, t_list *env, char mode);
char	**concatenate(t_list *list);
void	execute(char **commands, t_list	*env);

// --- ENVIRONMENT UTILS --- //

t_list	*append_argument(char *str);
t_list	*copy_env(char *env[]);
char	*find_env(t_list *env, char *str);
void	delete_env(t_list *env, char *str);
void	do_the_rest(t_list *list, char *str);
void	new_env_var(t_list *env, char *newvar, char *value);
void	replace_env(t_list *env, char *var_to_change, char *str);

// --- PIPING UTILS --- //

// --- EXTRAS --- //

void	zerofree(char *s);
void	arrayfree(char **arr);
void	quicc_copy(char *dest, char *src);
char	**list_to_char(t_list *env);

// --- BUNGIE SPECIFIC --- //

void	error_bad_format(char *src);
void	check_failed_memory(void *str);
void	error_system(int mode, char *file);

// --- DEBUG SWITCHES --- //

# ifndef DEBUG
#  define DEBUG 0
# endif
# ifndef __APPLE__
#  define __APPLE__ 0
# endif
# define HOSTNAME "HOSTNAME"
# ifdef WSL2
#  undef HOSTNAME
#  define HOSTNAME "NAME"
# endif
#endif
