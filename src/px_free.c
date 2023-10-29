/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:57:37 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/29 08:57:08 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex(t_pipex *pipex)
{
	if (pipex->argv)
	{
		free_split (pipex->argv);
		pipex->argv = NULL;
	}
	if (pipex->path)
	{
		free_split (pipex->path);
		pipex->path = NULL;		
	}
	if (pipex->cmd)
	{
		free (pipex->cmd);
		pipex->path = NULL;	
	}
}

void	close_pipe(t_pipex *pipex)
{
	close (pipex->infile);
	close (pipex->outfile);
	close (pipex->fd[0]);
	close (pipex->fd[1]);
}
