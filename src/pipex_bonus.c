/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:11:32 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/26 09:02:30 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	begin_fork(t_pipex *pipex, char **argv, char **envp)
{
	int	i;

	i = 0;
	while (++i < pipex->cmd_nb + 1)
		child_process (i, pipex, argv, envp);
	close_pipe (pipex);
	i = -1;
	while (++i < pipex->cmd_nb - 1)
		waitpid (pipex->pid[i], NULL, 0);
	waitpid (pipex->pid[pipex->cmd_nb - 1], &pipex->status, 0);
	free_pipex (pipex);
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
	count_argv (argc, argv, &pipex);
	pipex.path = make_path(envp);
	create_pipe (&pipex);
	get_infile (argv, &pipex);
	dup2(pipex.infile, pipex.fd[0][0]);
	if (pipex.infile > -1)
		close(pipex.infile);
	pipex.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(pipex.outfile, pipex.fd[pipex.cmd_nb][1]);
	if (pipex.infile > -1)
		close(pipex.outfile);
	pipex.pid = (int *) malloc (pipex.cmd_nb * sizeof(int *));
	begin_fork (&pipex, argv, envp);
	return (EXIT_SUCCESS);
}
