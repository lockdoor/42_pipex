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

void	new_parse_cmd(t_pipex *pipex, char *argv, char **envp)
{
	pipex->argv = px_split (argv, 32);

	if (pipex->argv == NULL)
	{
		exit_error("split command", pipex, 127);
	}
	// should command not found 127
	if (!*pipex->argv)
	{
		exit_error(*pipex->argv, pipex, 127);
	}
	// if full path
	if (ft_strchr(*pipex->argv, '/'))
	{
		if (access(*pipex->argv, R_OK | X_OK) == 0)
			pipex->cmd = ft_strdup(*pipex->argv);
		else if (errno == EACCES)
			exit_error(*pipex->argv, pipex, 126);
		else 
			exit_error(*pipex->argv, pipex, 127);
		return ;
	}

	// ft_printf ("begin find path\n");
	// join path
	char	**path;
	char	*tmp;

	pipex->path = make_path (envp);
	// ft_printf ("pipex->path: %p\n", pipex->path);
	if (!pipex->path || !*pipex->path)
		exit_error(*pipex->path, pipex, 127);
	pipex->cmd = ft_strjoin ("/", *pipex->argv);
	if (!pipex->cmd)
		exit_error(*pipex->argv, pipex, 127);
	// ft_printf ("pipex->cmd: %s\n", pipex->cmd);
	path = pipex->path;
	while (*path)
	{
		tmp = ft_strjoin (*path, pipex->cmd);
		if (!tmp)
			exit_error(*pipex->argv, pipex, 127);
		if (access(tmp, F_OK) == 0)
		{
			if (access(tmp, R_OK | X_OK) == 0)
			{
				free (pipex->cmd);
				pipex->cmd = tmp;
			}
			else if (errno == 13)
				exit_error(*pipex->argv, pipex, 126);
			else 
				exit_error(*pipex->argv, pipex, 127);
			return ;
		}
		free (tmp);
		path++ ;
	}
	errno = 2;
	exit_error (*pipex->argv, pipex, 127);
}