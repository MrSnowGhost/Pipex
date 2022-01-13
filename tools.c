/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:32:45 by ybensell          #+#    #+#             */
/*   Updated: 2022/01/13 10:47:32 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	**get_env(char **env)
{
	int i;
	char	*tmp;
	char	**str;

	i = 0;
	char path[5] = "PATH=";
	while (env[i])
	{
		if (ft_strncmp(env[i], path, 5) == 0)
			break;
		i++;
	}

	if (env[i] == NULL)  //Handle Error
		return (NULL);   	
	tmp = env[i];
	str = ft_split2(tmp + 5, ':'); //protect
	return (str);
}

char	*find_path(char *cmd, char **str)
{
	int		i;
	char	*tmp;
	int		result;

	i = 0;
	while (str[i])
	{
		tmp = ft_strjoin(str[i], cmd);
		result = access(tmp, F_OK);
		if (result == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}


