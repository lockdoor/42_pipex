/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_manage_pipe_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:34:46 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/31 11:54:06 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	px_error_pipe(t_pipex *pipex, int n)
{
	int	i;

	i = -1;
	while (++i <= n)
		free (pipex->fd[i]);
	free (pipex->fd);
	pipex->fd = NULL;
	px_exit_error (WRONG_PIPE, pipex, EXIT_FAILURE);
}

void	px_create_pipe(t_pipex *pipex)
{
	int	i;

	pipex->fd = (int **) malloc((pipex->cmd_nb + 1) * sizeof(int **));
	if (!pipex->fd)
		px_exit_error (WRONG_PIPE, pipex, EXIT_FAILURE);
	i = -1;
	while (++i < pipex->cmd_nb + 1)
	{
		pipex->fd[i] = malloc (sizeof(int) * 2);
		if (!pipex->fd[i])
			px_error_pipe (pipex, i - 1);
		if (pipe(pipex->fd[i]) == -1)
			px_error_pipe (pipex, i);
	}
}

void	px_close_pipe(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->cmd_nb + 1)
	{
		if (pipex->fd[i][0] != -1)
			close (pipex->fd[i][0]);
		if (pipex->fd[i][1] != -1)
			close (pipex->fd[i][1]);
		free (pipex->fd[i]);
		pipex->fd[i] = NULL;
	}
	free (pipex->fd);
	pipex->fd = NULL;
}
