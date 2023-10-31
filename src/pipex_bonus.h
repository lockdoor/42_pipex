/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:22:45 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/31 08:20:40 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

// ft_bytezero, ft_splite, ft_strjoin, ft_strchr, ft_memcmp
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define WRONG_COMMAND "command not found"
# define WRONG_PIPE "Error on create pipe"
# define WRONG_FORK "Fork error"
# define WRONG_HERE_DOC "Error on read here_doc"
# define HERE_DOC ".here_doc_tmp"

typedef struct s_pipex
{
	char	*cmd;
	char	**argv;
	char	**path;
	int		here_doc;
	int		cmd_nb;
	int		**fd;
	int		*pid;
	int		infile;
	int		outfile;
	int		status;
}	t_pipex;

// px_parse_cmd.c
char	*parse_cmd(t_pipex *pipex, char *argv);
char	**make_path(char **envp);

// manage_pipe_bonus.c
void	create_pipe(t_pipex *pipex);
void	close_pipe(t_pipex *pipex);

// child_process_bonus.c
void	child_process(int i, t_pipex *pipex, char **argv, char **envp);

// here_doc_bonus.c
int		count_argv(int argc, char **argv, t_pipex *pipex);
void	get_infile(char **argv, t_pipex *pipex);

// px_utils.c
void	free_split(void *data);
void	exit_cmd_not_found(char *cmd, t_pipex *pipex);
void	exit_error(char *s, t_pipex *pipex, int exit_code);

// px_free_bonus.c
void	free_pipex(t_pipex *pipex);

// px_split.c
char	**px_split(const char *s, char c);

#endif
