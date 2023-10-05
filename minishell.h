/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:27:13 by fclivaz           #+#    #+#             */
/*   Updated: 2023/10/05 18:46:23 by fclivaz          ###    LAUSANNE.CH      */
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
	int		ecode;
	pid_t	pid;
	char	*pwd;
	t_list	*env;
	t_token	*commands;
}	t_minishell;

// --- PARSING --- //

t_list	*interparse(char *rl, t_list *env);
int		count_quotes(char *str, t_list *env, int *size, char q);
int		copy_quotes(char *ntrp, char *str, t_list *env, char q);
int		copy_var(char *ntrp, char *str, t_list *env);
int		expand_var(char *str, t_list *env, int *size);

// --- ENVIRONMENT --- //

char	**env_to_array(t_list *env);
char	*find_env(t_list *env, char *str);
void	delete_env(t_minishell *msdata, char *str);
void	new_env_var(t_minishell *msdata, char *newvar, char *value);
void	replace_env(t_list *env, char *var_to_change, char *str);
void	init_mshell(char *av, char *env[], t_minishell *msdata);

// --- PIPING --- //

// --- EXECUTION --- //

char	**token_to_array(t_list *list);
char	*make_pathed(char *str, t_list *env);
int		execute(t_token *tkn, t_minishell *msdata);

// --- MEMORY MANAGEMENT --- //

void	zerofree(char *s);
void	arrayfree(char **arr);
void	free_token(t_token *tkn);
void	freexit(t_minishell *msdata);

// --- EXTRA UTILS --- //

char	*relative_dir(char **path, char *pwd);
char	*readline_proompter(int ecode, t_list *env, char *pwd);
void	quicc_copy(char *dest, char *src);

// --- BUILT-IN COMMANDS --- //

int		echo(t_token *tkn);
int		cd(t_token *tkn, t_minishell *msdata);
int		env(t_token *tkn, t_minishell *msdata);
int		mexport(t_token *tkn, t_minishell *msdata);
int		unset(t_token *tkn, t_minishell *msdata);

// --- BUNGIE SPECIFIC --- //

void	*error_bad_format(char *src);
void	*memchk(void *str);
void	*error_unsupported_character(char c);
int		error_system(int mode, char *file);

// --- DEFINE HELL --- //

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
# define ERED	"\033[1;31m"
# define EGRN	"\033[1;32m"
# define EYEL	"\033[1;33m"
# define CPRP	"\033[1m\x1b[38;2;123;91;227m"
# define CGLD	"\033[1m\x1b[38;2;235;155;28m"
# define CBBL	"\033[1m\x1b[38;2;2;224;242m"
# define CBLU	"\x1b[38;2;2;224;242m"
# define RSET	"\x1b[0m"
#endif
