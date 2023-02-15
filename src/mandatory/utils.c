/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcorrea- <hcorrea-@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:09:48 by gda-cruz          #+#    #+#             */
/*   Updated: 2023/02/15 16:42:56 by hcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_args(t_a *a, char **argv)
{
	int		i;
	int		j;
	int		k;
	char	**args;

	args = (char **)malloc(sizeof(char *) * (a->cmd_num + 1));
	if (!args)
		err_handler(a, 0, "Error getting the commands");
	i = 0;
	j = 2;
	while (i < a->cmd_num)
	{
		k = 0;
		while (argv[j][k] == ' ' || argv[j][k] == '\t')
			k++;
		if (argv[j][0] != '/')
			args[i] = ft_strjoin("/", &(argv[j][k]));
		else
			args[i] = ft_strdup(&(argv[j][k]));
		i++;
		j++;
	}
	args[i] = NULL;
	return (args);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*joined;

	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s1 || !s2 || !joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		joined[i] = s2[j];
		i++;
		j++;
	}
	joined[i] = '\0';
	return (joined);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;
	int		length;

	length = 0;
	i = 0;
	while (s[length])
		length++;
	dup = (char *)malloc(sizeof(char) * (length + 1));
	if (!s || !dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i])
	{
		if (i < (n - 1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}
