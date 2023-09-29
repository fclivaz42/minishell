/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:27:13 by fclivaz           #+#    #+#             */
/*   Updated: 2023/09/30 00:31:54 by fclivaz          ###    LAUSANNE.CH      */
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

typedef struct s_token
{
	int				fd_in;
	int				fd_out;
	t_list			*words;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_minishell
{
	pid_t	pid;
	char	*pwd;
	t_list	*env;
	t_token	*commands;
}	t_minishell;

// --- MINISHELL --- //

t_list	*ms_fullparse(char *str, t_list *env);
char	*readline_proompter(t_list *env, char *pwd);
char	*interpreter(char *raw, t_list *env, char mode);
char	**concatenate(t_list *list);
int		execute(t_token *tkn, t_minishell *msdata);

// --- ENVIRONMENT UTILS --- //

void	copy_env(char *env[], t_minishell *msdata);
char	*find_env(t_list *env, char *str);
void	delete_env(t_minishell *msdata, char *str);
void	new_env_var(t_minishell *msdata, char *newvar, char *value);
void	replace_env(t_list *env, char *var_to_change, char *str);

// --- PIPING UTILS --- //

// --- EXTRAS --- //

void	zerofree(char *s);
void	arrayfree(char **arr);
void	free_token(t_token *tkn);
void	freexit(t_minishell *msdata);
void	quicc_copy(char *dest, char *src);
char	**list_to_char(t_list *env);

// --- BUILT-IN COMMANDS --- //

int		echo(t_token *tkn);
int		cd(t_token *tkn, t_minishell *msdata);
int		env(t_token *tkn, t_minishell *msdata);
int		mexport(t_token *tkn, t_minishell *msdata);
int		unset(t_token *tkn, t_minishell *msdata);

// --- BUNGIE SPECIFIC --- //

void	*error_bad_format(char *src);
void	*memchk(void *str);
void	*error_system(int mode, char *file);
void	*error_unsupported_character(char c);

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
