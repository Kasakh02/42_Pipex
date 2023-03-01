/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:06:47 by hcorrea-          #+#    #+#             */
/*   Updated: 2023/03/01 08:58:49 by hcorrea-         ###   ########.fr       */
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
# include <unistd.h>

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
	int		heredoc;
}				t_pip;

void	init(t_pip *pip, int argc, char **argv, char **env);
void	pre_hd(t_pip *pip, int argc, char **argv);
void	heredoc(char **argv, int fd);
void	openfile(t_pip *pip, int argc, char **argv);
char	**path_finder(t_pip *pip, char **env);

void	init_cmd(t_pip *pip);
void	get_cmd_path(t_pip *pip);
void	filter_cmd(t_pip *pip);

char	*ft_strrchr(const char *str, int c);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	exe(t_pip *pip, char **env);

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
char	*get_next_line(int fd);

#endif
