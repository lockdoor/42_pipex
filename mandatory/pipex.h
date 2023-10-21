/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:22:45 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/20 13:17:58 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// access, execve, close, pipe
# include <unistd.h>

// perror
# include <stdio.h>

// free
# include <stdlib.h>

// open
# include <fcntl.h>

// ft_bytezero, ft_splite
# include <libft.h>
# include <ft_printf.h>

# define WRONG_ARGS_NUMBER "Wrong number of argument"
# define WRONG_INFILE "Can not access Infile"
# define WRONG_OUTFILE "Can not access Outfile"
# define WRONG_COMMAND "command not found"
# define WRONG_PIPE "Error on create pipe"
# define WRONG_EXEC "Error on execute"
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
}	t_pipex;

// debug
void	print_split(char **sp);

// utils.c
void	free_split(void *data);
void	free_pipex(t_pipex *pipex);

// t_bool	parse_cmd(t_pipex *pipex, char *argv, char **envp);

#endif

