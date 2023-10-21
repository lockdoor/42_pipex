/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:22:08 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/21 07:06:26 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "sys/wait.h"
#include <sys/types.h>
#include <string.h>
#include <errno.h>

void	exit_error(char *s, t_pipex *pipex, int exit_code)
{
	// ft_printf ("exit_error: %d, %s\n", errno, strerror(errno));
	perror (s);
	free_pipex (pipex);
	// if (errno)
	// 	exit (127);
	exit (exit_code);
}

char	*parse_cmd(t_pipex *pipex, char *argv)
{
	char	**path;
	char	*tmp;

	pipex->argv = ft_split (argv, 32);
	if (pipex->argv == NULL || !*pipex->argv)
		return (NULL);
	if (ft_strchr(*pipex->argv, '/') && access (*pipex->argv, X_OK) != -1)
		return (*pipex->argv);
	// else
	// 	return (NULL);
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
		exit_error (WRONG_FORK, pipex, EXIT_FAILURE);
	if (pipex->pid1 == 0)
	{
		pipex->cmd = parse_cmd (pipex, argv[2]);
		if (pipex->cmd == NULL)
		{
			write (2, pipex->argv[0], ft_strlen(pipex->argv[0]));
			write (2, ": ", 2);
			write (2, WRONG_COMMAND, ft_strlen(WRONG_COMMAND));
			write (2, "\n", 1);
			free_pipex (pipex);
			exit (127);
		}
		if (pipex->infile != -1)
		{
			close (pipex->outfile);
			close (pipex->fd[0]);
			dup2 (pipex->infile, STDIN_FILENO);
			close (pipex->infile);			
			dup2 (pipex->fd[1], STDOUT_FILENO);
			close (pipex->fd[1]);
			if (execve (pipex->cmd, pipex->argv, envp) == -1)
				exit_error (WRONG_EXEC, pipex, errno);			
		}
		exit (EXIT_FAILURE);
	}
}

void	second_child(t_pipex *pipex, char **argv, char **envp)
{
	if ( pipex->pid2 == -1)
		exit_error (WRONG_FORK, pipex, EXIT_FAILURE);
	if (pipex->pid2 == 0)
	{
		pipex->cmd = parse_cmd (pipex, argv[3]);
		if (pipex->cmd == NULL)
		{
			write (2, pipex->argv[0], ft_strlen(pipex->argv[0]));
			write (2, ": ", 2);
			write (2, WRONG_COMMAND, ft_strlen(WRONG_COMMAND));
			write (2, "\n", 1);
			free_pipex (pipex);
			exit(127);
		}
		close (pipex->infile);
		close (pipex->fd[1]);
		dup2 (pipex->fd[0], STDIN_FILENO);
		close (pipex->fd[0]);
		dup2 (pipex->outfile, STDOUT_FILENO);
		close (pipex->outfile);
		if (execve (pipex->cmd, pipex->argv, envp) == -1)
			exit_error (WRONG_EXEC, pipex, errno);
	}
	// exit (127);
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
		exit_error (WRONG_ARGS_NUMBER, &pipex, EXIT_FAILURE);

	/* open file */
	pipex.infile = open (argv[1], O_RDONLY);
	if (pipex.infile < 1)
		perror (argv[1]);
	pipex.outfile = open (argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex.outfile < 0)
		exit_error (argv[argc - 1], &pipex, errno);

	/* parse path */
	pipex.path = make_path(envp);
	if (pipex.path == NULL)
		exit_error ("wrong path", &pipex, EXIT_FAILURE);

	/* make pipe */
	if (pipe(pipex.fd) == -1)
		exit_error (WRONG_PIPE, &pipex, errno);
	
	/* first process */
	// if (pipex.infile != -1)
	// {
		pipex.pid1 = fork ();
		first_child (&pipex, argv, envp);		
	// }

	/* second process */
	pipex.pid2 = fork ();
	second_child (&pipex, argv, envp);		
	
	close (pipex.fd[0]);
	close (pipex.fd[1]);
	close (pipex.infile);
	close (pipex.outfile);
	int	status;
	waitpid (pipex.pid1, NULL, 0);
	waitpid (pipex.pid2, &status, 0);
	// ft_printf ("status: %d\n", status);
	// if (WIFEXITED(status))
	if (status)
	{	
		// status = WEXITSTATUS(status);
		// ft_printf ("status: %d, %d, %d\n", 
		// status, WEXITSTATUS(status), WIFEXITED(status));
		return (WEXITSTATUS(status));
	}

	return (EXIT_SUCCESS);
}
