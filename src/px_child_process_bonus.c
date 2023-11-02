/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_child_process_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:23:27 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/02 10:22:40 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	px_check_file_open(int i, char **argv, t_pipex *pipex)
{
	if (i == 1)
	{
		if (pipex->here_doc)
		{
			if (access(HERE_DOC, R_OK) == -1)
				px_exit_error (HERE_DOC, pipex, EXIT_FAILURE);
		}
		else if (access(argv[1], R_OK) == -1)
			px_exit_error (argv[1], pipex, EXIT_FAILURE);
	}
	if (i == pipex->cmd_nb
		&& access (argv[pipex->cmd_nb + 2 + pipex->here_doc], W_OK) == -1)
		px_exit_error (argv[pipex->cmd_nb + 2 + pipex->here_doc], pipex, 1);
}

void	px_child_process(int i, t_pipex *pipex, char **argv, char **envp)
{
	pipex->pid[i - 1] = fork();
	if (pipex->pid[i - 1] == -1)
		px_exit_error (WRONG_FORK, pipex, EXIT_FAILURE);
	if (pipex->pid[i - 1] == 0)
	{
		dup2 (pipex->fd[i - 1][0], STDIN_FILENO);
		dup2 (pipex->fd[i][1], STDOUT_FILENO);
		px_close_pipe (pipex);
		px_check_file_open (i, argv, pipex);
		px_parse_cmd(pipex, argv[i + 1 + pipex->here_doc], envp);
		px_execute_cmd (pipex, envp);
	}
}
