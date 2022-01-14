/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:31:20 by ybensell          #+#    #+#             */
/*   Updated: 2022/01/14 18:57:26 by ybensell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_var
{
	int		result;
	int		i;
	int		id_1;
	int		id_2;
	int		fd;
	int		fd2;
	int		pip[2];
	char	**cmd;
	char	*path;
	char	**paths;	
}	t_var;

char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
int		ft_strncmp(char *s1, char *s2, int n);
void	get_env(char **env, t_var *var);
char	**ft_split(char const *s, char c);
char	**ft_split2(char const *s, char c);
size_t	ft_strlen(const char *s);
void	find_path(t_var *var);
void	free_tab(char **str);
void	free_var(t_var *var);
void	error_free(t_var *var);
#endif
