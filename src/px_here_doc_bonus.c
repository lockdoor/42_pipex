/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_here_doc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:48:25 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/03 08:19:24 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	px_get_infile(char **argv, t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->infile = open (HERE_DOC, O_RDONLY);
	else
		pipex->infile = open (argv[1], O_RDONLY);
}

static void	px_read_here_doc(char **argv, t_pipex *pipex)
{
	char	*line;

	line = NULL;
	while (1)
	{
		write (STDOUT_FILENO, "heredoc> ", 9);
		line = get_next_line (STDIN_FILENO);
		if (!line || ft_strncmp (line, argv[2], ft_strlen (argv[2]) + 1) == 10)
			break ;
		write (pipex->infile, line, ft_strlen(line));
		free (line);
	}
	close (pipex->infile);
	free (line);
}

void	px_count_argv(int argc, char **argv, t_pipex *pipex)
{
	if (argc < 5)
	{
		errno = EINVAL;
		px_exit_error (*argv, pipex, EXIT_FAILURE);
	}
	pipex->here_doc = 0;
	if (!ft_memcmp(argv[1], "here_doc", 9))
	{
		pipex->here_doc = 1;
		if (argc - 1 < 5)
		{
			errno = EINVAL;
			px_exit_error (*argv, pipex, EXIT_FAILURE);
		}
		pipex->infile = open (HERE_DOC, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (pipex->infile != -1)
			px_read_here_doc (argv, pipex);
	}
	pipex->cmd_nb = argc - 3 - pipex->here_doc;
}
