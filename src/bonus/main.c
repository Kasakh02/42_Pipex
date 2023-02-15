/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:31:53 by gda-cruz          #+#    #+#             */
/*   Updated: 2023/02/15 16:35:05 by hcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_cmd(t_a *a, char **envp)
{
	if (pipe(a->pipe_fd) == -1)
		err_handler(a, 2, "Error creating the pipe");
	a->pid = fork();
	if (a->pid == -1)
		err_handler(a, 2, "Error forking");
	if (a->pid == 0)
	{
		filter_cmd(a);
		setup_cmd(a);
		execve(a->cmd_path, a->cmds, envp);
		err_handler(a, 2, "Error executing command");
	}
	close(a->pipe_fd[1]);
	dup2(a->pipe_fd[0], STDIN_FILENO);
}

int	main(int argc, char **argv, char **envp)
{
	t_a	a;

	if (argc < 5)
	{
		write(STDERR, "Invalid number of arguments.\n", 29);
		exit(EXIT_FAILURE);
	}
	setup(&a, argc, argv, envp);
	a.i = 0;
	while (a.i < a.cmd_num)
	{
		run_cmd(&a, envp);
		a.i++;
	}
	while (a.i--)
		wait(NULL);
	free_two(&a);
	return (0);
}
