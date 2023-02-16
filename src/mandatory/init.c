/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:08:48 by gda-cruz          #+#    #+#             */
/*   Updated: 2023/02/16 12:12:13 by hcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	setup(t_a *a, int argc, char **argv, char **envp)
{
	openfile(a, argc, argv);
	a->cmd_num = argc - 3;
	a->args = get_args(a, argv);
	a->path = path_finder(a, envp);
}

void	openfile(t_a *a, int argc, char **argv)
{
	a->in_file = open(argv[1], O_RDONLY);
	a->out_file = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (a->in_file == -1 || a->out_file == -1)
		err_handler(a, 0, "Error while setting up");
}

char	**path_finder(t_a *a, char **envp)
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
		err_handler(a, 1, "Error while setting up");
	path = ft_split(line, ':');
	return (path);
}
