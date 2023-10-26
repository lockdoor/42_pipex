/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:23:27 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/26 10:59:02 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*parse_cmd2(t_pipex *pipex)
{
	char	**path;
	char	*tmp;

	pipex->cmd = ft_strjoin ("/", *pipex->argv);
	path = pipex->path;
	if (!pipex->cmd)
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

static char	*parse_cmd(t_pipex *pipex, char *argv)
{
	pipex->argv = ft_split (argv, 32);
	if (pipex->argv == NULL || !*pipex->argv)
		return (NULL);
	if (ft_strchr(*pipex->argv, '/'))
	{
		if (access(*pipex->argv, X_OK) == 0)
			return (*pipex->argv);
		else if (errno == 13)
			exit_error (*pipex->argv, pipex, 126);
		else
			exit_error (*pipex->argv, pipex, 127);
			// exit_wrong_cmd (*pipex->argv, pipex);
	}
	return (parse_cmd2(pipex));
}

void	check_file_open(int i, char **argv, t_pipex *pipex)
{
	if (i == 1)
	{
		if (pipex->here_doc)
		{
			if (access(HERE_DOC, R_OK) == -1)
				exit_error (HERE_DOC, pipex, EXIT_FAILURE);
		}
		else if (access(argv[1], R_OK) == -1)
			exit_error (argv[1], pipex, EXIT_FAILURE);
	}
	if (i == 1 && pipex->infile == -1)
	{
		errno = 2;
		exit_error (argv[1], pipex, errno);
	}
	if (i == pipex->cmd_nb
		&& access (argv[pipex->cmd_nb + 2 + pipex->here_doc], W_OK) == -1)
		exit_error (argv[pipex->cmd_nb + 2 + pipex->here_doc], pipex, 1);
	if (i == pipex->cmd_nb && pipex->outfile == -1)
	{
		errno = 2;
		exit_error (argv[pipex->cmd_nb + 2], pipex, EXIT_FAILURE);
	}
}

void	child_process(int i, t_pipex *pipex, char **argv, char **envp)
{
	pipex->pid[i - 1] = fork();
	if (pipex->pid[i - 1] == -1)
		exit_error (WRONG_FORK, pipex, EXIT_FAILURE);
	if (pipex->pid[i - 1] == 0)
	{
		check_file_open (i, argv, pipex);
		if (!pipex->path)
			exit_wrong_cmd (*pipex->argv, pipex);
		pipex->cmd = parse_cmd (pipex, argv[i + 1 + pipex->here_doc]);
		if (pipex->cmd == NULL)
			exit_wrong_cmd (*pipex->argv, pipex);
		dup2 (pipex->fd[i - 1][0], STDIN_FILENO);
		dup2 (pipex->fd[i][1], STDOUT_FILENO);
		close_pipe (pipex);
		if (execve(pipex->cmd, pipex->argv, envp) == -1)
			exit_error (WRONG_EXEC, pipex, 127);
	}
}
