/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:06:47 by hcorrea-          #+#    #+#             */
/*   Updated: 2023/02/14 15:02:27 by hcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define INFILE 0
# define OUTFILE 1

char	*path_join(char *path, char *bin);
int		str_ncmp(char *str1, char *str2, int n);
int		str_ichr(char *str, char c);
char	*str_ndup(char *str, unsigned int n);
char	**str_split(char *str, char sep);

#endif
