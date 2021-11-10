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

char	child(t_cmd *p, int fd[], int x)
{
	int		file;

	printf("%s\n", p->exec_arg1);
	printf("%s\n", p->my_argv[x + 2]);
	close(fd[0]);
	if (x == 0)
	{
		file = open("file1.txt", O_RDONLY);
		if (file == -1)
			printf("erro Joao\n");
		dup2(file, STDIN_FILENO);
	}
	if (x == 1)
	{
		file = open("file2.txt", O_RDONLY);
		if (file == -1)
			printf("erro Joao\n");
		dup2(file, STDOUT_FILENO);
	}
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (execve(p->exec_arg1, p->exec_arg2, NULL) < 0)
		return (5);
	return(0);
}

void	fill_p(t_cmd *p, int argc, char **argv)
{
	p->my_argc = argc;
	p->my_argv = argv;
	//p->file1 = ft_strdup(argv[1]);
}

void	exec_pid(t_cmd *p, int pid, int fd[], int x)
{

	p->exec_arg2 = ft_split(p->my_argv[x + 2], ' ');
	p->exec_arg1 = ft_strjoin("/usr/bin/", p->exec_arg2[0]);
	if (pid == 0)
		child(p, fd, x);
	free(p->exec_arg1);
	ft_clear_split(p->exec_arg2);
	close(fd[1]);
}

int	main(int argc, char **argv)
{
	t_cmd		p;
	int			fd[2];
	int			pid1;
	int			pid2;

	create_pipe(fd);
	fill_p(&p, argc, argv);
	
	pid1 = create_fork();

	exec_pid(&p, pid1, fd, 0);
	
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);

	create_pipe(fd);
	pid2 = create_fork();
	
	exec_pid(&p, pid2, fd, 1);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	close(fd[0]);
	printf("JOÂO PÈ DE ARROZ");
	return (0);
}
