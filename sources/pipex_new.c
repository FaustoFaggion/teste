#include "pipex.h"
#include <stdio.h>

void	ft_clear_split(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

int	create_pipe(int fd[])
{
	if (pipe(fd) == -1)
		return (1);
	return(0);
}

int	create_fork()
{
	int pid;

	pid =  fork();
	if (pid < 0)
		return (2);
	return (pid);
}

// ./pipex file1.txt "grep Este" "cat" "wc" file2.txt (Atualizar Makefile)
int	main(int argc, char *argv[])
{
	t_cmd	p;
	int		fd[2];
	int		pid;
	int		file;
	
	if (argc < 0)
		return (0);

	p.exec_arg1 = ;
	file = open(p.exec_arg1, O_RDONLY);
	create_pipe(fd);
	pid = create_fork();
	if (pid == 0)
	{
		dup2(file, STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "arquivo", NULL);
	}
	waitpid(pid, NULL, 0);
	free(p.exec_arg1);
	close(fd[0]);
	close(fd[1]);
	return (0);
}