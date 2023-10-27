/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 08:16:46 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/27 08:17:09 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_pipex(t_pipex *pipex)
{
	if (pipex->argv)
		free_split (pipex->argv);
	if (pipex->path)
		free_split (pipex->path);
	if (pipex->cmd)
		free (pipex->cmd);
	if (pipex->fd)
		close_pipe (pipex);
	if (pipex->pid)
		free (pipex->pid);
	if (pipex->here_doc)
		unlink (HERE_DOC);
}
