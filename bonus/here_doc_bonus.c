/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 06:48:25 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/24 12:01:42 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	get_infile(char **argv, t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->infile = open (HERE_DOC, O_RDONLY);
	else
		pipex->infile = open (argv[1], O_RDONLY);
}

void	read_here_doc(char **argv, t_pipex *pipex)
{
	char	*line;

	line = NULL;
	while (1)
	{
		write (STDOUT_FILENO, "heredoc> ", 9);
		line = get_next_line (STDIN_FILENO);
		if (ft_strncmp (line, argv[2], ft_strlen (argv[2]) + 1) == 10)
			break ;
		write (pipex->infile, line, ft_strlen(line));
		free (line);
	}
	close (pipex->infile);
	free (line);
}

int	count_argv(int argc, char **argv, t_pipex *pipex)
{
	if (!ft_memcmp(argv[1], "here_doc", 9))
	{
		pipex->here_doc = 1;
		if (5 > argc - 1)
			exit_error (WRONG_ARGS_NUMBER, pipex, EXIT_FAILURE);
		pipex->infile = open (HERE_DOC, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (pipex->infile != -1)
			read_here_doc (argv, pipex);
	}
	if (5 > argc)
		exit_error (WRONG_ARGS_NUMBER, pipex, EXIT_FAILURE);
	pipex->cmd_nb = argc - 3 - pipex->here_doc;
	return (argc - pipex->here_doc);
}
