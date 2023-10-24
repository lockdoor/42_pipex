/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:34:46 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/24 13:56:58 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_pipe(t_pipex *pipex, int n)
{
	int	i;

	i = -1;
	while (++i <= n)
		free (pipex->fd[i]);
	free (pipex->fd);
	pipex->fd = NULL;
	exit_error (WRONG_PIPE, pipex, EXIT_FAILURE);
}

void	create_pipe(t_pipex *pipex)
{
	int	i;

	pipex->fd = (int **) malloc((pipex->cmd_nb + 1) * sizeof(int **));
	if (!pipex->fd)
		exit_error (WRONG_PIPE, pipex, EXIT_FAILURE);
	i = -1;
	while (++i < pipex->cmd_nb + 1)
	{
		pipex->fd[i] = malloc (sizeof(int) * 2);
		if (!pipex->fd[i])
			error_pipe (pipex, i - 1);
		if (pipe(pipex->fd[i]) == -1)
			error_pipe (pipex, i);
	}
}

void	close_pipe(t_pipex *pipex)
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
	}
	free (pipex->fd);
	pipex->fd = NULL;
}
