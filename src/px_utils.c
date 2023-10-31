/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:25:26 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/31 11:57:56 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_free_split(void *data)
{
	char	**split;

	split = (char **) data;
	if (!split)
		return ;
	while (*split)
		free (*split++);
	free (data);
}

void	px_exit_cmd_not_found(char *cmd, t_pipex *pipex)
{
	write (2, cmd, ft_strlen(cmd));
	write (2, ": ", 2);
	write (2, WRONG_COMMAND, ft_strlen(WRONG_COMMAND));
	write (2, "\n", 1);
	px_free_pipex (pipex);
	exit (127);
}

void	px_exit_error(char *s, t_pipex *pipex, int exit_code)
{
	perror (s);
	px_free_pipex (pipex);
	exit (exit_code);
}

/* in case no such file, it come from argument have path but no file exited */
void	px_execute_cmd(t_pipex *pipex, char **envp)
{
	if (execve(pipex->cmd, pipex->argv, envp) == -1)
	{
		if (errno == ENOEXEC)
		{
			if (access(pipex->cmd, R_OK | X_OK) == -1)
			{
				perror (pipex->cmd);
				px_free_pipex (pipex);
				exit (126);
			}
			px_free_pipex (pipex);
			exit (0);
		}
		perror (pipex->cmd);
		px_free_pipex (pipex);
		if (errno == EACCES)
			exit (126);
		else
			exit (127);
	}
}
