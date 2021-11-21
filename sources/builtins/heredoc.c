#include "../../includes/minishell.h"

static int	child_process(t_token *point, char *stop, int fd[2])
{
	char	*line;

	close(fd[0]);
	point->fd1 = fd[1];
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, stop))
			break ;
		ft_putendl_fd(line, point->fd1);
		free(line);
	}
	close(point->fd1);
	return (0);
}

static void	parent_process(t_token *point, pid_t pid, int fd[2])
{
	close(fd[1]);
	waitpid(pid, NULL, 0);
	point->fd0 = fd[0];
}

void	heredoc(t_token *point)
{
	int		i;
	int		fd[2];
	pid_t	pid;
	char	**stop;

	stop = ft_split(point->stopheredoc, ' ');
	i = 0;
	while (stop[i])
	{
		if (pipe(fd) < 0)
		{
			perror("Error");
			g_status = 1;
			exit(g_status);
		}
		pid = fork();
		if (!pid)
			exit(child_process(point, stop[i], fd));
		else
			parent_process(point, pid, fd);
		i++;
	}
	free(stop);
}