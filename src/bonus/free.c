/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:18:47 by gda-cruz          #+#    #+#             */
/*   Updated: 2023/02/17 13:59:15 by hcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	free_fd(t_pip *pip)
{
	if (pip->in_file)
		close(pip->in_file);
	if (pip->out_file)
		close(pip->out_file);
}

void	free_args(t_pip *pip)
{
	int	i;

	i = 0;
	free_fd(pip);
	while (pip->args[i])
		free(pip->args[i++]);
	free(pip->args);
}

void	free_path_cmd(t_pip *pip)
{
	int	i;

	i = 0;
	free_args(pip);
	while (pip->path[i])
		free(pip->path[i++]);
	free(pip->path);
	if (pip->pid == 0)
	{
		if (pip->cmds)
		{
			i = 0;
			while (pip->cmds[i])
				free(pip->cmds[i++]);
			free(pip->cmds);
		}
	}
}

void	put_error(t_pip *pip, int err_code, char *err)
{
	if (err_code == 0)
		free_fd(pip);
	else if (err_code == 1)
		free_args(pip);
	else if (err_code == 2)
		free_path_cmd(pip);
	perror(err);
	exit(EXIT_FAILURE);
}
