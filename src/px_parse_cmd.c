#include "pipex.h"

static char	**px_make_path(char **envp)
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

/* if not found in path it's exit command not found */
static void	px_join_path(t_pipex *pipex)
{
	char	**path;
	char	*cmd;

	path = pipex->path;
	while (*path)
	{
		cmd = ft_strjoin (*path, pipex->cmd);
		if (!cmd)
			exit_cmd_not_found (*pipex->argv, pipex);
		if (access(cmd, F_OK) == 0)
		{
			free (pipex->cmd);
			pipex->cmd = cmd;
			return ;
		}
		free (cmd);
		path++ ;
	}
	exit_cmd_not_found(*pipex->argv, pipex);
}

/*
**	1.	if no argv in zsh: permission denied, bash: command not found
**	2.	if have path sent this command to execve
**	3	in case no path
**	3.1	if file exited sent this command to execve
**	3.2 if not exited it's error command not found exit: 127
*/

/* if command -eq "" in zsh: permission denied, bash: command not found */

void	px_parse_cmd(t_pipex *pipex, char *argv, char **envp)
{
	pipex->argv = px_split (argv, 32);
	if (!pipex->argv || !*pipex->argv)
		exit_cmd_not_found ("", pipex);
	if (ft_strchr(*pipex->argv, '/'))
	{
		pipex->cmd = ft_strdup(*pipex->argv);
		return ;
	}
	pipex->path = px_make_path (envp);
	if (!pipex->path || !*pipex->path)
	{
		if (access(*pipex->argv, F_OK) == 0)
			pipex->cmd = ft_strdup(*pipex->argv);
		else
			exit_cmd_not_found (*pipex->argv, pipex);
		return ;
	}	
	pipex->cmd = ft_strjoin ("/", *pipex->argv);
	if (!pipex->cmd)
		exit_cmd_not_found (*pipex->argv, pipex);
	px_join_path (pipex);
}
