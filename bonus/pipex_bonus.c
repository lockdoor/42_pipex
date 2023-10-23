/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:11:32 by pnamnil           #+#    #+#             */
/*   Updated: 2023/10/21 16:54:50 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// int main(int argc, char **argv)
// {
// 	(void) argc;
// 	t_pipex pipex;

// 	ft_bzero (&pipex, sizeof(t_pipex));
// 	int cnt = count_argv (argv, &pipex);
// 	ft_printf ("cnt: %d\n", cnt);
// 	return (0);
// }

/* 
** number of pipe eq number of command plus 1,
** because first pipe use in parent then rest pipe
** use in each command of child
*/
int main(int argc, char *argv[], char *envp[]) {
	t_pipex	pipex;

	ft_bzero(&pipex, sizeof(t_pipex));

	if (count_argv (argc, argv, &pipex) < 5)
	// if (argc < 5)
		exit_error (WRONG_ARGS_NUMBER, &pipex, EXIT_FAILURE);
	
	pipex.path = make_path(envp, &pipex);

	/* this task should work in count_argv */
	// pipex.cmd_nb = argc - 3;

	/* if create pipe failed, it's exit by function */
	create_pipe (&pipex);

    // pipex.infile = open(argv[1], O_RDONLY);
	get_infile (argv, &pipex);
    dup2(pipex.infile, pipex.fd[0][0]);
    close(pipex.infile);

    pipex.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    dup2(pipex.outfile, pipex.fd[pipex.cmd_nb][1]);
    close(pipex.outfile);

	/* make pid[] */
	pipex.pid = (int *) malloc (pipex.cmd_nb * sizeof(int *)); 
    for (int i = 1; i < pipex.cmd_nb + 1; i++) {
		child_process (i, &pipex, argv, envp);
    }

	/* close pipe */
	close_pipe (&pipex);
	// free_pipex (&pipex);

	for (int i = 0; i < pipex.cmd_nb - 1; i++){
		waitpid (pipex.pid[i], NULL, 0);
	}

	waitpid (pipex.pid[pipex.cmd_nb - 1], &pipex.status, 0);
	free_pipex (&pipex);
	if (pipex.status)
		return (WEXITSTATUS(pipex.status));
    return (EXIT_SUCCESS);
}
