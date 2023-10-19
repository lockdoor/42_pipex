/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:22:08 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/19 09:21:07 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "sys/wait.h"

void	exit_error(char *s, t_pipex *pipex)
{
	free_pipex (pipex);
	perror (s);
	exit (EXIT_FAILURE);
}

char	*parse_cmd(t_pipex *pipex, char *argv)
{
	char	**path;
	char	*tmp;

	pipex->argv = ft_split (argv, 32);
	if (pipex->argv == NULL || !*pipex->argv)
		return (NULL);
	pipex->cmd = ft_strjoin ("/", *pipex->argv);
	if (!pipex->cmd)
		return (NULL);
	path = pipex->path;
	while (*path)
	{
		tmp = ft_strjoin (*path, pipex->cmd);
		if (!tmp)
			return (NULL);
		if (access(tmp, X_OK) != -1)
			return (tmp);
		free (tmp);
		path++ ;
	}
	return (NULL);
}

void	first_child(t_pipex *pipex, char **argv, char **envp)
{
	if ( pipex->pid1 == -1)
		exit_error (WRONG_FORK, pipex);
	if (pipex->pid1 == 0)
	{
		pipex->cmd = parse_cmd (pipex, argv[2]);
		if (pipex->cmd == NULL)
			exit_error (WRONG_COMMAND, pipex);
		close (pipex->outfile);
		close (pipex->fd[0]);
		dup2 (pipex->infile, STDIN_FILENO);
		close (pipex->infile);
		dup2 (pipex->fd[1], STDOUT_FILENO);
		close (pipex->fd[1]);
		if (execve (pipex->cmd, pipex->argv, envp) == -1)
			exit_error (WRONG_EXEC, pipex);
	}
}

void	second_child(t_pipex *pipex, char **argv, char **envp)
{
	if ( pipex->pid2 == -1)
		exit_error (WRONG_FORK, pipex);
	if (pipex->pid2 == 0)
	{
		pipex->cmd = parse_cmd (pipex, argv[3]);
		if (pipex->cmd == NULL)
			exit_error (WRONG_COMMAND, pipex);
		close (pipex->infile);
		close (pipex->fd[1]);
		dup2 (pipex->fd[0], STDIN_FILENO);
		close (pipex->fd[0]);
		dup2 (pipex->outfile, STDOUT_FILENO);
		close (pipex->outfile);
		if (execve (pipex->cmd, pipex->argv, envp) == -1)
			exit_error (WRONG_EXEC, pipex);
	}
}


char	**make_path(char **envp)
{
	while (*envp && ft_memcmp(*envp, "PATH=", 5))
		envp++ ;
	if (*envp == NULL)
		return (NULL);
	return (ft_split(*envp + 5, ':'));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex pipex;
	
	ft_bzero (&pipex, sizeof(pipex));

	/* check number of arguments */
	if (argc != 5)
		exit_error (WRONG_ARGS_NUMBER, &pipex);

	/* open file */
	pipex.infile = open (argv[1], O_RDONLY);
	if (pipex.infile == -1)
		exit_error (WRONG_INFILE, &pipex);
	pipex.outfile = open (argv[argc - 1], O_WRONLY);
	if (pipex.outfile == -1)
		exit_error (WRONG_OUTFILE, &pipex);

	/* parse path */
	pipex.path = make_path(envp);
	if (pipex.path == NULL)
		exit_error ("wrong path", &pipex);
	// print_split (pipex.path);

	/* make pipe */
	if (pipe(pipex.fd) == -1)
		exit_error (WRONG_PIPE, &pipex);
	ft_printf ("pid: %d, ppid: %d, fd[0]: %d\n",
		getpid(), getppid(), pipex.fd[0]);
	ft_printf ("pid: %d, ppid: %d, fd[1]: %d\n",
		getpid(), getppid(), pipex.fd[1]);
	
	/* first child */
	pipex.pid1 = fork ();
	first_child (&pipex, argv, envp);

	/* second child */
	pipex.pid2 = fork ();
	second_child (&pipex, argv, envp);
	
	close (pipex.fd[0]);
	close (pipex.fd[1]);
	close (pipex.infile);
	close (pipex.outfile);
	waitpid (pipex.pid1, NULL, 0);
	waitpid (pipex.pid2, NULL, 0);
	

	
	return (0);
}
