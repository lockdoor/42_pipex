/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:01:15 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/21 15:49:40 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	find_idx_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_memcmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++ ;
	}
	return (-1);
}

char	**find_path(char **envp)
{
	int		idx;
	char	**path;

	idx = find_idx_path(envp);
	if (idx == -1)
		return (NULL);
	path = ft_split (envp[idx], ':');
	if (!path)
		return (NULL);
	return (path);
}

t_bool	make_cmd(t_pipex *pipex)
{
	char	*fullpath;
	int		i;

	pipex->cmd = ft_strjoin ("/", *pipex->argv);
	if (pipex->cmd)
	{
		i = -1;
		while (pipex->path[++i])
		{
			fullpath = ft_strjoin (pipex->path[i], pipex->cmd);
			if (!fullpath)
				break ;
			if (access(fullpath, X_OK) != -1)
			{
				free (pipex->cmd);
				pipex->cmd = fullpath;
				return (TRUE);
			}
			free (fullpath);
		}
	}
	return (FALSE);
}

t_bool	parse_cmd(t_pipex *pipex, char *argv, char **envp)
{
	pipex->argv = ft_split (argv, 32);
	if (!pipex->argv)
		return (FALSE);
	pipex->path = find_path (envp);
	if (!pipex->path)
	{
		free_pipex (pipex);
		return (FALSE);
	}
	if (!*pipex->argv || !*pipex->path)
	{
		free_pipex (pipex);
		return (FALSE);
	}
	if (!make_cmd (pipex))
	{
		free_pipex (pipex);
		return (FALSE);
	}
	return (TRUE);
}
