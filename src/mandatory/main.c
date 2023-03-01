/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:31:53 by gda-cruz          #+#    #+#             */
/*   Updated: 2023/03/01 08:54:11 by hcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (unsigned char)c)
			return (&((char *)str)[i]);
		i--;
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	char	temp;

	temp = (unsigned char)c;
	while (temp != *s)
	{
		if (*s == 0)
			return (0);
		++s;
	}
	return ((char *)s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	l;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (start >= l)
	{
		sub = malloc(sizeof(char));
		if (!sub)
			return (NULL);
		*sub = '\0';
		return (sub);
	}
	if (l < len)
		return (ft_strdup((char *)s + start));
	i = 0;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (start < l && i < len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

void	exe(t_pip *pip, char **env)
{
	if (pipe(pip->pipe_fd) == -1)
		put_error(pip, 2, "Error creating the pipe");
	pip->pid = fork();
	if (pip->pid == -1)
		put_error(pip, 2, "Error forking");
	if (pip->pid == 0)
	{
		filter_cmd(pip);
		init_cmd(pip);
		execve(pip->cmd_path, pip->cmds, env);
		put_error(pip, 2, "Error executing command");
	}
	close(pip->pipe_fd[1]);
	dup2(pip->pipe_fd[0], STDIN_FILENO);
}

int	main(int argc, char **argv, char **env)
{
	t_pip	pip;

	if (argc < 5)
	{
		write(STDERR, "Invalid number of arguments.\n", 29);
		exit(EXIT_FAILURE);
	}
	init(&pip, argc, argv, env);
	pip.i = 0;
	while (pip.i < pip.cmd_num)
	{
		exe(&pip, env);
		pip.i++;
	}
	while (pip.i--)
		wait(NULL);
	free_path_cmd(&pip);
	return (0);
}
