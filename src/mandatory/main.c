/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:31:53 by gda-cruz          #+#    #+#             */
/*   Updated: 2023/02/17 13:52:06 by hcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

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
	free_fd(&pip);
	return (0);
}
