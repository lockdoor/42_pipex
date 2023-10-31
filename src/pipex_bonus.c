/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:11:32 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/31 12:34:30 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	px_begin_fork(t_pipex *pipex, char **argv, char **envp)
{
	int	i;

	i = 0;
	while (++i < pipex->cmd_nb + 1)
		px_child_process (i, pipex, argv, envp);
	px_close_pipe (pipex);
	i = -1;
	while (++i < pipex->cmd_nb - 1)
		waitpid (pipex->pid[i], NULL, 0);
	waitpid (pipex->pid[pipex->cmd_nb - 1], &pipex->status, 0);
	px_free_pipex (pipex);
	if (pipex->status)
		exit (WEXITSTATUS(pipex->status));
}

/* 
** number of pipe eq number of command plus 1,
** because first pipe use in parent then rest pipe
** use in each command of child
*/

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	ft_bzero(&pipex, sizeof(t_pipex));
	px_count_argv (argc, argv, &pipex);
	px_create_pipe (&pipex);
	px_get_infile (argv, &pipex);
	dup2(pipex.infile, pipex.fd[0][0]);
	if (pipex.infile > -1)
		close(pipex.infile);
	pipex.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(pipex.outfile, pipex.fd[pipex.cmd_nb][1]);
	if (pipex.infile > -1)
		close(pipex.outfile);
	pipex.pid = (int *) malloc (pipex.cmd_nb * sizeof(int *));
	if (!pipex.pid)
		px_exit_error ("pipex.pid", &pipex, errno);
	px_begin_fork (&pipex, argv, envp);
	return (EXIT_SUCCESS);
}
