/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:25:26 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/27 08:02:42 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(void *data)
{
	char	**split;

	split = (char **) data;
	while (*split)
		free (*split++);
	free (data);
}

void	exit_wrong_cmd(char *cmd, t_pipex *pipex)
{
	write (2, cmd, ft_strlen(cmd));
	write (2, ": ", 2);
	write (2, WRONG_COMMAND, ft_strlen(WRONG_COMMAND));
	write (2, "\n", 1);
	free_pipex (pipex);
	exit (127);
}

void	exit_error(char *s, t_pipex *pipex, int exit_code)
{
	perror (s);
	free_pipex (pipex);
	exit (exit_code);
}
