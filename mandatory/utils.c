/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:25:26 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/19 07:52:13 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(void *data)
{
	char	**split;
	int	i;

	split = (char **) data;
	i = -1;
	while (split[++i])
		free (split[i]);
	free (split);
}

void	free_pipex(t_pipex *pipex)
{
	if (pipex->argv)
		free_split (pipex->argv);
	if (pipex->path)
		free_split (pipex->path);
	if (pipex->cmd)
		free (pipex->cmd);
}
