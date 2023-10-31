/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 10:26:19 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/31 08:11:37 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* 
** open can throw error such as No such file or permission denied
*/ 

/*
** check file
** check command
** dup
** execve
*/

/* in case no such file, it come from argument have path but no file exited */
static void	execute_cmd(t_pipex *pipex, char **envp)
{
	if (execve(pipex->cmd, pipex->argv, envp) == -1)
	{
		if (errno == ENOEXEC)
		{
			if (access(pipex->cmd, R_OK | X_OK) == -1)
			{
				perror (pipex->cmd);
				free_pipex (pipex);
				exit (126);
			}
			free_pipex (pipex);
			exit (0);
		}
		perror (pipex->cmd);
		free_pipex (pipex);
		if (errno == EACCES)
			exit (126);
		else
			exit (127);
	}
}

static void	fork_error(t_pipex *pipex, char **argv)
{
	close (pipex->fd[0]);
	close (pipex->fd[1]);
	perror (*argv);
	exit (EXIT_FAILURE);
}

void	first_child(t_pipex *pipex, char **argv, char **envp)
{
	if (pipex->pid1 == -1)
		fork_error (pipex, argv);
	if (pipex->pid1 == 0)
	{
		pipex->infile = open (argv[1], O_RDONLY);
		if (pipex->infile == -1)
			exit_error (argv[1], pipex, EXIT_FAILURE);
		px_parse_cmd(pipex, argv[2], envp);
		close (pipex->fd[0]);
		dup2 (pipex->infile, STDIN_FILENO);
		close (pipex->infile);
		dup2 (pipex->fd[1], STDOUT_FILENO);
		close (pipex->fd[1]);
		execute_cmd (pipex, envp);
	}
}

void	second_child(t_pipex *pipex, char **argv, char **envp)
{
	if (pipex->pid2 == -1)
		fork_error (pipex, argv);
	if (pipex->pid2 == 0)
	{
		pipex->outfile = open (argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfile == -1)
			exit_error (argv[4], pipex, EXIT_FAILURE);
		px_parse_cmd(pipex, argv[3], envp);
		close (pipex->fd[1]);
		dup2 (pipex->fd[0], STDIN_FILENO);
		close (pipex->fd[0]);
		dup2 (pipex->outfile, STDOUT_FILENO);
		close (pipex->outfile);
		execute_cmd (pipex, envp);
	}
}
