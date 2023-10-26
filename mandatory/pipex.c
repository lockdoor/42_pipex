/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:22:08 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/25 17:15:20 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	ft_bzero (&pipex, sizeof(pipex));
	if (argc != 5)
	{
		errno = EINVAL;
		exit_error ("pipex", &pipex, EXIT_FAILURE);
	}
	pipex.path = make_path(envp);
	pipex.infile = open (argv[1], O_RDONLY);
	pipex.outfile = open (argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (pipe(pipex.fd) == -1)
		exit_error (WRONG_PIPE, &pipex, errno);
	pipex.pid1 = fork ();
	first_child (&pipex, argv, envp);
	pipex.pid2 = fork ();
	second_child (&pipex, argv, envp);
	close_pipe (&pipex);
	waitpid (pipex.pid1, NULL, 0);
	waitpid (pipex.pid2, &pipex.status, 0);
	free_pipex (&pipex);
	if (pipex.status)
		return (WEXITSTATUS(pipex.status));
	return (EXIT_SUCCESS);
}
