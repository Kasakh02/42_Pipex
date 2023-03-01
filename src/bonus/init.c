/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:08:48 by gda-cruz          #+#    #+#             */
/*   Updated: 2023/03/01 10:47:01 by hcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	init(t_pip *pip, int argc, char **argv, char **envp)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
		pre_hd(pip, argc, argv);
	else
		openfile(pip, argc, argv);
	pip->cmd_num = argc - 3 - pip->heredoc;
	pip->args = get_args(pip, argv);
	pip->path = path_finder(pip, envp);
}

void	pre_hd(t_pip *pip, int argc, char **argv)
{
	int	tmp;

	if (argc < 6)
	{
		write(STDERR, "Heredoc needs at least 6 args to run\n", 37);
		exit(EXIT_FAILURE);
	}
	pip->heredoc = 1;
	pip->out_file = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	tmp = open(".store", O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (pip->out_file == -1 || tmp == -1)
		put_error(pip, 0, "Error while setting up");
	heredoc(argv, tmp);
	close(tmp);
	pip->in_file = open(".store", O_RDONLY);
	if (pip->in_file == -1)
		put_error(pip, 0, "Error while setting up");
}

void	heredoc(char **argv, int fd)
{
	char	*tmp;
	char	*lim;
	char	*line;

	tmp = ft_strdup(argv[2]);
	lim = ft_strjoin(tmp, "\n");
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (ft_strlen(line) == ft_strlen(lim))
			if (!ft_strncmp(lim, line, ft_strlen(lim)))
				break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(tmp);
	free(lim);
	free(line);
}

void	openfile(t_pip *pip, int argc, char **argv)
{
	pip->heredoc = 0;
	pip->in_file = open(argv[1], O_RDONLY);
	pip->out_file = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (pip->in_file == -1 || pip->out_file == -1)
		put_error(pip, 0, "Error while setting up");
}

char	**path_finder(t_pip *pip, char **envp)
{
	int		i;
	char	*line;
	char	**path;

	i = 0;
	line = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			line = ft_strdup(&(envp[i][5]));
			break ;
		}
		i++;
	}
	if (line == NULL)
		put_error(pip, 1, "Error while setting up");
	path = ft_split(line, ':');
	free(line);
	return (path);
}
