/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 13:08:34 by averheij       #+#    #+#                */
/*   Updated: 2019/11/28 12:46:28 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

/*
** 1 : A line has been read
** 0 : EOF has been reached
** -1 : An error happened
*/

char		*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		l1;
	int		l2;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strrchr(s1, '\0');
	l2 = ft_strrchr(s2, '\0');
	res = (char*)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!res)
		return (NULL);
	res[l1 + l2] = '\0';
	i = 0;
	while (i < l1 || i < l2)
	{
		if (i < l1)
			res[i] = s1[i];
		if (i < l2)
			res[i + l1] = s2[i];
		i++;
	}
	return (res);
}

int		extract_line(char **persistent, char **line, int c)
{
	char			*temp;

	// printf("\tCHR _%d_%d_\n", c, ft_strchr(*persistent, c));
	// printf("\tRES _%d_%s_\n", ft_strchr(*persistent, '\n'), *persistent);
	*line = ft_substr(*persistent, 0, ft_strchr(*persistent, c));
	// printf("\tLINE _%s_\n", *line);
	if (c == '\0')
	{
		// perror("EOF free res");
		free(*persistent);
		*persistent = NULL;
		return (0);
	}
	temp = ft_substr(*persistent, ft_strchr(*persistent, c) + 1,
		ft_strrchr(*persistent, '\0') - ft_strchr(*persistent, c));
	free(*persistent);
	*persistent = temp;
	// printf("\tRESF _%d_%s_\n", ft_strchr(*persistent, '\n'), *persistent);
	return (1);
}

int		read_line(char **persistent, int fd)
{
	size_t		readc;
	char		*temp;
	char		buf[BUFFER_SIZE + 1];

	readc = 1;
	while (readc && ft_strchr(*persistent, '\n') == -1)
	{
		// perror("Reading");
		readc = read(fd, buf, BUFFER_SIZE);
		buf[readc] = '\0';
		if (!readc)
		{
			*persistent = ft_strjoin(*persistent, buf);
			// printf("\t\\0 RES _%d_%s_\n", ft_strchr(*persistent, '\0'), *persistent);
			break ;
		}
		temp = ft_strjoin(*persistent, buf);
		free(*persistent);
		*persistent = temp;
		// printf("\tREADC BUF _%zu_%s_\n", readc, buf);
		// printf("\t\\N RES _%d_%s_\n", ft_strchr(*persistent, '\n'), *persistent);
	}
}

int		get_next_line(int fd, char **line)
{
	static char		*persistent;

	if (!persistent)
	{
		// perror("persistent init");
		persistent = (char*)malloc(sizeof(char));
		persistent[0] = '\0';
	}
	if (read(fd, 0, 0) == -1)
		return (-1);
	// printf("\t\\N RESI _%d_%s_\n", ft_strchr(persistent, '\n'), persistent);
	read_line(&persistent, fd);
	// perror("Extracting");
	if (ft_strchr(persistent, '\n') != -1)
		return (extract_line(&persistent, line, '\n'));
	else
		return (extract_line(&persistent, line, '\0'));
}
