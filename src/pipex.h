/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:22:45 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/27 15:17:12 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// access, execve, close, pipe
# include <unistd.h>

// wait, waitpid
# include <sys/wait.h>
# include <sys/types.h>

// perror, strerror
# include <stdio.h>

// free
# include <stdlib.h>

// open
# include <fcntl.h>

// errno
# include <errno.h>

// ft_bytezero, ft_splite, ft_strjoin, ft_strchr
# include "libft.h"
# include "ft_printf.h"

// # define WRONG_ARGS_NUMBER "Wrong number of argument"
// # define WRONG_INFILE "Can not access Infile"
// # define WRONG_OUTFILE "Can not access Outfile"
# define WRONG_COMMAND "command not found"
# define WRONG_PIPE "Error on create pipe"
// # define WRONG_EXEC "Error on execute"
# define WRONG_FORK "Fork error"

typedef struct s_pipex
{
	char	*cmd;
	char	**argv;
	char	**path;
	int		fd[2];
	int		pid1;
	int		pid2;
	int		infile;
	int		outfile;
	int		status;
}	t_pipex;

// debug
// void	print_split(char **sp);

// px_utils.c
void	free_split(void *data);
void	close_pipe(t_pipex *pipex);
void	exit_wrong_cmd(char *cmd, t_pipex *pipex);
void	exit_error(char *s, t_pipex *pipex, int exit_code);

// child_process.c
void	first_child(t_pipex *pipex, char **argv, char **envp);
void	second_child(t_pipex *pipex, char **argv, char **envp);

// px_parse_cmd.c
char	*parse_cmd(t_pipex *pipex, char *argv);
char	**make_path(char **envp);

// px_free.c
void	free_pipex(t_pipex *pipex);
void	close_pipe(t_pipex *pipex);

// px_split.c
char	**px_split(const char *s, char c);

#endif
