/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:46:57 by gda-cruz          #+#    #+#             */
/*   Updated: 2023/02/17 13:59:03 by hcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	filter_cmd(t_pip *pip)
{
	close(pip->pipe_fd[0]);
	if (pip->i == 0)
	{
		dup2(pip->in_file, STDIN_FILENO);
		dup2(pip->pipe_fd[1], STDOUT_FILENO);
	}
	else if (pip->i == (pip->cmd_num - 1))
		dup2(pip->out_file, STDOUT_FILENO);
	else
		dup2(pip->pipe_fd[1], STDOUT_FILENO);
}

void	init_cmd(t_pip *pip)
{
	pip->cmds = ft_split(pip->args[pip->i], ' ');
	if (!pip->cmds)
		put_error(pip, 2, "Error getting commands");
	get_cmd_path(pip);
	if (!pip->cmd_path)
		put_error(pip, 2, "Error getting command path");
}

static int	valid_path(t_pip *pip)
{
	char	*temp;
	int		ok;
	int		i;

	i = -1;
	while (pip->path[++i])
	{
		temp = ft_strjoin(pip->path[i], pip->cmds[0]);
		ok = access(temp, F_OK);
		if (ok < 0)
		{
			free(temp);
			continue ;
		}
		else
		{
			pip->cmd_path = ft_strdup(temp);
			free(temp);
			return (1);
		}
	}
	return (0);
}

void	get_cmd_path(t_pip *pip)
{
	int		ok;
	int		valid;

	ok = access(pip->cmds[0], F_OK);
	if (ok == 0)
	{
		pip->cmd_path = ft_strdup(pip->cmds[0]);
		return ;
	}
	valid = valid_path(pip);
	if (valid)
		return ;
	put_error(pip, 2, "Error getting command path");
}
