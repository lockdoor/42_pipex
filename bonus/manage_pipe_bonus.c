/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:34:46 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/22 16:35:48 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	create_pipe(t_pipex *pipex)
{
	pipex->fd = (int **) malloc((pipex->cmd_nb + 1) * sizeof(int **));
	if (!pipex->fd)
		exit_error (WRONG_PIPE, pipex, EXIT_FAILURE);
    for (int i = 0; i < pipex->cmd_nb + 1; i++) {
		pipex->fd[i] = malloc (sizeof(int) * 2);
		if (!pipex->fd[i])
		{
			for (int j = 0; j < i; j++)
				free (pipex->fd[j]);
			free (pipex->fd);
			exit_error (WRONG_PIPE, pipex, EXIT_FAILURE);
		}
		/* should protect if error pipe */
        pipe(pipex->fd[i]);
    }
}

void	close_pipe(t_pipex *pipex)
{
	for (int i = 0; i < pipex->cmd_nb + 1; i++){
		close (pipex->fd[i][0]);
		close (pipex->fd[i][1]);
		free (pipex->fd[i]);
	}
	free (pipex->fd);
	pipex->fd = NULL;
}
