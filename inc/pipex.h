/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:06:47 by hcorrea-          #+#    #+#             */
/*   Updated: 2023/02/15 16:34:31 by hcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <wait.h>
# include <fcntl.h>
# include <fcntl.h>
# include <errno.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_a
{
	int		in_file;
	int		out_file;
	int		cmd_num;
	char	**args;
	char	**path;
	int		pipe_fd[2];
	int		i;
	pid_t	pid;
	char	*cmd_path;
	char	**cmds;
}				t_a;


void	setup(t_a *a, int argc, char **argv, char **envp);
void	openfile(t_a *a, int argc, char **argv);
char	**path_finder(t_a *a, char **envp);

void	setup_cmd(t_a *a);
void	get_cmd_path(t_a *a);
void	run_cmd(t_a *a, char **envp);
void	filter_cmd(t_a *a);

void	err_handler(t_a *a, int err_code, char *err);
void	free_zero(t_a *a);
void	free_one(t_a *a);
void	free_two(t_a *a);

char	**get_args(t_a *a, char **argv);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	**ft_split(char const *s, char c);

#endif
