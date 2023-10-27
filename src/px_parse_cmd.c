/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:52:48 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/27 15:16:48 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*parse_cmd2(t_pipex *pipex)
{
	char	**path;
	char	*tmp;

	pipex->cmd = ft_strjoin ("/", *pipex->argv);
	path = pipex->path;
	if (!pipex->cmd || !path)
		return (NULL);
	while (*path)
	{
		tmp = ft_strjoin (*path, pipex->cmd);
		if (!tmp)
		{
			free (pipex->cmd);
			return (NULL);
		}
		if (access(tmp, X_OK) != -1)
		{
			free (pipex->cmd);
			return (tmp);
		}
		free (tmp);
		path++ ;
	}
	free (pipex->cmd);
	return (NULL);
}

char	*parse_cmd(t_pipex *pipex, char *argv)
{
	pipex->argv = px_split (argv, 32);
	if (pipex->argv == NULL || !*pipex->argv)
		return (NULL);
	if (ft_strchr(*pipex->argv, '/'))
	{
		if (access(*pipex->argv, R_OK | X_OK) == 0)
			return (ft_strdup(*pipex->argv));
		else if (errno == 13)
			exit_error (*pipex->argv, pipex, 126);
		else
			exit_error (*pipex->argv, pipex, 127);
	}
	return (parse_cmd2(pipex));
}

char	**make_path(char **envp)
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
