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

// char	**make_path(char **envp, t_pipex *pipex)
// {
// 	char	**path;

// 	while (*envp && ft_memcmp(*envp, "PATH=", 5))
// 		envp++ ;
// 	if (*envp == NULL)
// 		exit_error ("wrong path", pipex, EXIT_FAILURE);
// 	path = ft_split(*envp + 5, ':');
// 	if (!path)
// 		exit_error ("wrong path", pipex, EXIT_FAILURE);
// 	return (path);
// }

int main(int argc, char *argv[], char *envp[]) {
    int fd_n = argc - 2;

	//wrong in norminate, should malloc instead
    int fd[fd_n][2];
    for (int i = 0; i < fd_n; i++) {
        pipe(fd[i]);
    }

    int infile = open(argv[1], O_RDONLY);
    dup2(infile, fd[0][0]);
    close(infile);

    int outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    dup2(outfile, fd[fd_n - 1][1]);
    close(outfile);

    char *cmd[] = {"/bin/cat", "/usr/bin/wc", NULL};
    char *arg[][2] = {{cmd[0], NULL}, {cmd[1], NULL}};

    for (int i = 1; i < fd_n; i++) {
        int pid = fork();
        if (pid == 0) {
            close(fd[i - 1][1]);
            dup2(fd[i - 1][0], STDIN_FILENO);
            close(fd[i - 1][0]);
            dup2(fd[i][1], STDOUT_FILENO);
            close(fd[i][1]);
            if (execve(cmd[i - 1], arg[i - 1], envp) == -1){
				perror (cmd[i - 1]);
			}
        }
		
    }
	for (int i = 0; i < fd_n; i++){
		close (fd[i][0]);
		close (fd[i][1]);
	}
    return 0;
}

