/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:08:48 by gda-cruz          #+#    #+#             */
/*   Updated: 2023/02/17 13:58:48 by hcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	init(t_pip *pip, int argc, char **argv, char **envp)
{
	openfile(pip, argc, argv);
	pip->cmd_num = argc - 3;
	pip->args = get_args(pip, argv);
	pip->path = path_finder(pip, envp);
}

void	openfile(t_pip *pip, int argc, char **argv)
{
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
	return (path);
}
