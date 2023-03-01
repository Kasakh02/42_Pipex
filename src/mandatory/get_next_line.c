/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:27:22 by hcorrea-          #+#    #+#             */
/*   Updated: 2023/03/01 08:58:59 by hcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"
#define BUFFER_SIZE 32

static	int	nl_index(char *matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (matrix[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

static char	*cleanup_crew(char **matrix)
{
	char	*line;
	char	*tmp;
	int		i;

	if (!*matrix || **matrix == '\0')
		return (NULL);
	i = nl_index(*matrix);
	if (ft_strchr(*matrix, '\n'))
	{
		line = ft_substr(*matrix, 0, i + 1);
		tmp = ft_substr(*matrix, i + 1, ft_strlen(*matrix) - i - 1);
		free(*matrix);
		*matrix = tmp;
		if (**matrix != '\0')
			return (line);
	}
	else
		line = ft_strdup(*matrix);
	free(*matrix);
	*matrix = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	int			rd;
	char		*buff;
	char		*tmp;
	static char	*matrix[FOPEN_MAX];

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	rd = read(fd, buff, BUFFER_SIZE);
	while (rd > 0)
	{
		buff[rd] = '\0';
		if (!matrix[fd])
			matrix[fd] = ft_strdup("");
		tmp = ft_strjoin(matrix[fd], buff);
		free(matrix[fd]);
		matrix[fd] = tmp;
		if (ft_strchr(matrix[fd], '\n'))
			break ;
		rd = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (cleanup_crew(&matrix[fd]));
}
