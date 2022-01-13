/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:27:55 by ybensell          #+#    #+#             */
/*   Updated: 2022/01/13 10:47:29 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char*	exec_cmd(char *cmd, char **env)
{
	char **str;
	char **paths;
	char *path;


	str = ft_split(cmd, ' '); //free
	if (access(str[0], F_OK) != 0)
	{
		paths = get_env(env);
		path = find_path(str[0], paths);	
	}
	else
		path = str[0];
	return (path);	
}

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDWR | O_CREAT, 0777);
	return (fd);
}

int	check_read(char *path)
{
	int	result;
	
	result = access(path,F_OK);
	if ( result == 0)
	{
		result = access(path,R_OK);
		if (result == 0)
			return (1);
		else
		{
			perror("Error :");
			return (0);
		}
	}
	perror("Error :");
	return (0);
}

int	main(int argc, char **argv,char **env)
{
 	int	i;
	int	fd;
	int fd2;
	int piip[2];
	char **str;
	char *path;

	if (argc == 5)
	{
		pipe(piip);
		i = check_read(argv[1]);
		if (i == 1)
		{
			fd = open_file(argv[1]);
			fd2 = open_file(argv[4]);
	
			if (fd == -1 || fd2 == -1)
			{
				perror("Error :");
				return (0);
			}
			i = fork();
			if (i == 0)
			{
				close(piip[0]);
				path = exec_cmd(argv[2], env);
				dup2(piip[1], 1);
				dup2(fd, 0);
				str = ft_split(argv[2], ' ');
				execve(path, str, env); // sus
			}
			waitpid(i, NULL, 0);
			if (i != 0)
			{	
				fd2 = open_file(argv[4]);
				close(piip[1]);
				path = exec_cmd(argv[3], env);
 				dup2(piip[0], 0);
				dup2(fd2, 1);
				str = ft_split(argv[3], ' ');
				execve(path, str , env);
			}
	}
	else
		write (1,"Usage ./pipex infile1 cmd cmd infile2\n", 38);
}
