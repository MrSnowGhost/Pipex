/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:27:55 by ybensell          #+#    #+#             */
/*   Updated: 2022/01/14 18:55:52 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	exec_cmd2(char **argv, char **env, t_var *var)
{
	var->fd2 = open(argv[4], O_WRONLY | O_CREAT, 0644);
	if (var->fd2 == -1)
		perror("Error");
	var->cmd = ft_split(argv[3], ' ');
	if (!(var->cmd))
		exit(0);
	if (access(var->cmd[0], F_OK) == 0)
		var->path = var->cmd[0];
	else
	{
		get_env(env, var);
		find_path(var);
	}
	close(var->pip[1]);
	if ((dup2(var->pip[0], 0)) == -1)
		error_free(var);
	if ((dup2(var->fd2, 1)) == -1)
		error_free(var);
	if ((execve(var->path, var->cmd, env) == -1))
		error_free(var);
}

void	exec_cmd1(char **argv, char **env, t_var *var)
{
	var->fd = open(argv[1], O_RDONLY);
	if (var->fd == -1)
		perror("Error");
	var->cmd = ft_split(argv[2], ' ');
	if (!(var->cmd))
		exit(0);
	if (access(var->cmd[0], F_OK) == 0)
		var->path = var->cmd[0];
	else
	{
		get_env(env, var);
		find_path(var);
	}
	close(var->pip[0]);
	if ((dup2(var->pip[1], 1) == -1))
		error_free(var);
	if ((dup2(var->fd, 0) == -1))
		error_free(var);
	if ((execve(var->path, var->cmd, env)) == -1)
		error_free(var);
}

int	check_read(char *path)
{
	int	result;

	result = access(path, F_OK);
	if (result == 0)
	{
		result = access(path, R_OK);
		if (result == 0)
			return (1);
		else
			perror("Error");
	}
	else
		perror("Error");
	return (0);
}

void	pipex(char **argv, char **env, t_var *var)
{
	if (pipe(var->pip) == -1)
		perror("pipe");
	var->i = check_read(argv[1]);
	if (var->i == 1)
	{	
		var->id_1 = fork();
		if (var->id_1 == -1)
			perror("Error");
		if (var->id_1 == 0)
			exec_cmd1(argv, env, var);
		var->id_2 = fork();
		if (var->id_2 == -1)
			perror("Error");
		if (var->id_2 == 0)
			exec_cmd2(argv, env, var);
	}
	close(var->pip[0]);
	close(var->pip[1]);
	waitpid(var->id_1, NULL, 0);
	waitpid(var->id_2, NULL, 0);
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	t_var	var;

	if (argc == 5)
		pipex(argv, env, &var);
	else
		write (1, "Usage : ./pipex \"file1\" \"cmd\" \"cmd\" \"file2\"\n", 43);
}
