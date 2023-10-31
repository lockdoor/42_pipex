/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:22:45 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/31 08:19:48 by pnamnil          ###   ########.fr       */
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

# define WRONG_COMMAND "command not found"

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

// px_utils.c
void	free_split(void *data);
void	exit_cmd_not_found(char *cmd, t_pipex *pipex);
void	exit_error(char *s, t_pipex *pipex, int exit_code);

// child_process.c
void	first_child(t_pipex *pipex, char **argv, char **envp);
void	second_child(t_pipex *pipex, char **argv, char **envp);

// px_parse_cmd.c
void	px_parse_cmd(t_pipex *pipex, char *argv, char **envp);

// px_free.c
void	free_pipex(t_pipex *pipex);

// px_split.c
char	**px_split(const char *s, char c);

#endif
