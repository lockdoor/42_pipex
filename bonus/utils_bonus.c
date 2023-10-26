/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:25:26 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/25 17:15:49 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_split(void *data)
{
	char	**split;

	split = (char **) data;
	while (*split)
		free (*split++);
	free (data);
}

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

/* if make path fail, exit with error code 1 */
char	**make_path(char **envp, t_pipex *pipex)
{
	char	**path;

	while (*envp && ft_memcmp(*envp, "PATH=", 5))
		envp++ ;
	if (*envp == NULL)
		return (NULL);
	path = ft_split(*envp + 5, ':');
	if (!path)
		return (NULL);
	return (path);
}
