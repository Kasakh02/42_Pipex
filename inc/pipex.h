/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:06:47 by hcorrea-          #+#    #+#             */
/*   Updated: 2023/02/17 14:06:24 by hcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <fcntl.h>
# include <errno.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_pip
{
	int		in_file;
	int		out_file;
	int		cmd_num;
	char	*cmd_path;
	char	**cmds;
	char	**args;
	char	**path;
	int		pipe_fd[2];
	pid_t	pid;
	int		i;
}				t_pip;


void	init(t_pip *pip, int argc, char **argv, char **env);
void	openfile(t_pip *pip, int argc, char **argv);
char	**path_finder(t_pip *pip, char **env);

void	init_cmd(t_pip *pip);
void	get_cmd_path(t_pip *pip);
void	exe(t_pip *pip, char **env);
void	filter_cmd(t_pip *pip);

void	put_error(t_pip *pip, int err_code, char *err);
void	free_fd(t_pip *pip);
void	free_args(t_pip *pip);
void	free_path_cmd(t_pip *pip);

char	**get_args(t_pip *pip, char **argv);
char	*ft_strjoin(char const *str1, char const *str2);
char	*ft_strdup(const char *str);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);

char	**ft_split(char const *str, char c);

#endif
