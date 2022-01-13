/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:31:20 by ybensell          #+#    #+#             */
/*   Updated: 2022/01/13 10:47:36 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_var
{
	int fd;
	int pip[2];
	char **cmd;
	char *path;
}
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
int		ft_strncmp(char *s1, char *s2, int n);
char	**get_env(char **env);
char	**ft_split(char const *s, char c);
char	**ft_split2(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*find_path(char *cmd, char **str);
#endif
