/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 08:16:46 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/31 11:57:20 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	px_free_pipex(t_pipex *pipex)
{
	if (pipex->argv)
	{
		px_free_split (pipex->argv);
		pipex->argv = NULL;
	}
	if (pipex->path)
	{
		px_free_split (pipex->path);
		pipex->path = NULL;
	}
	if (pipex->cmd)
	{
		free (pipex->cmd);
		pipex->cmd = NULL;
	}
	if (pipex->fd)
		px_close_pipe (pipex);
	if (pipex->pid)
		free (pipex->pid);
	if (access (HERE_DOC, F_OK) == 0)
		unlink (HERE_DOC);
}
