/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:57:37 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/31 12:37:28 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		pipex->path = NULL;
	}
}
