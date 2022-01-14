/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:32:45 by ybensell          #+#    #+#             */
/*   Updated: 2022/01/14 18:57:54 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	get_env(char **env, t_var *var)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
	{
		free_tab(var->cmd);
		write(2, "Error : Cannot find Shell command's path \n", 44);
		exit(0);
	}	
	tmp = env[i];
	var->paths = ft_split2(tmp + 5, ':');
	if (!(var->paths))
	{
		free_tab(var->cmd);
		exit(0);
	}
}

void	find_path(t_var *var)
{
	int		i;

	i = 0;
	while (var->paths[i])
	{
		var->path = ft_strjoin(var->paths[i], var->cmd[0]);
		if (!(var->paths))
		{
			free(var->cmd);
			free(var->paths);
			exit(0);
		}
		var->result = access(var->path, F_OK);
		if (var->result == 0)
		{
			free_tab(var->paths);
			return ;
		}
		free(var->path);
		i++;
	}
	free_tab(var->paths);
	free_tab(var->cmd);
	write(2, "Error : Command Not found\n", 26);
	exit(0);
}

void	free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_var(t_var *var)
{
	free_tab(var->cmd);
	free(var->path);
}

void	error_free(t_var *var)
{
	free_var(var);
	perror("Error");
}
