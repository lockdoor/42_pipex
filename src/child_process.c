/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 10:26:19 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/27 08:04:22 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex *pipex, char **argv, char **envp)
{
	if (pipex->pid1 == -1)
		exit_error (WRONG_FORK, pipex, EXIT_FAILURE);
	if (pipex->pid1 == 0)
	{
		if (access(argv[1], R_OK) == -1)
			exit_error (argv[1], pipex, errno);
		if (pipex->infile == -1)
		{
			errno = 2;
			exit_error (argv[1], pipex, EXIT_FAILURE);
		}
		if (!pipex->path)
			exit_wrong_cmd (*pipex->argv, pipex);
		pipex->cmd = parse_cmd (pipex, argv[2]);
		if (pipex->cmd == NULL)
			exit_wrong_cmd (*pipex->argv, pipex);
		dup2 (pipex->infile, STDIN_FILENO);
		dup2 (pipex->fd[1], STDOUT_FILENO);
		close_pipe (pipex);
		if (execve (pipex->cmd, pipex->argv, envp) == -1)
			exit (0);
	}
}

void	second_child(t_pipex *pipex, char **argv, char **envp)
{
	if (pipex->pid2 == -1)
		exit_error (WRONG_FORK, pipex, EXIT_FAILURE);
	if (pipex->pid2 == 0)
	{
		if (access(argv[4], W_OK) == -1)
			exit_error (argv[4], pipex, EXIT_FAILURE);
		if (pipex->outfile == -1)
		{
			errno = 2;
			exit_error (argv[4], pipex, EXIT_FAILURE);
		}
		if (!pipex->path)
			exit_wrong_cmd (*pipex->argv, pipex);
		pipex->cmd = parse_cmd (pipex, argv[3]);
		if (pipex->cmd == NULL)
			exit_wrong_cmd (*pipex->argv, pipex);
		dup2 (pipex->fd[0], STDIN_FILENO);
		dup2 (pipex->outfile, STDOUT_FILENO);
		close_pipe (pipex);
		if (execve (pipex->cmd, pipex->argv, envp) == -1)
			exit (0);
	}
}
