/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 13:08:34 by averheij       #+#    #+#                */
/*   Updated: 2019/11/27 15:13:05 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** 1 : A line has been read
** 0 : EOF has been reached
** -1 : An error happened
*/

char			*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	if (i < start)
		return (ft_strdup(""));
	sub = (char*)malloc(sizeof(char) *
		((i - start < len) ? i - start : len) + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, ((i - start < len) ? i - start : len) + 1);
	return (sub);
}

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

int		extract_line(char **reserves, char **line, int c)
{
	char			*temp;

	printf("\tCHR _%d_%d_\n", c, ft_strchr(*reserves, c));
	*line = ft_substr(*reserves, 0, ft_strchr(*reserves, c));
	printf("\tLINE _%s_\n", *line);
	if (c == '\0')
	{
		free(*reserves);
		return (0);
	}
	printf("\tRES _%d_%s_\n", ft_strchr(*reserves, '\n'), *reserves);
	temp = ft_substr(*reserves, ft_strchr(*reserves, c) + 1,
		ft_strrchr(*reserves, '\0') - ft_strchr(*reserves, c));
	free(*reserves);
	*reserves = temp;
	printf("\tRESF _%d_%s_\n", ft_strchr(*reserves, '\n'), *reserves);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char		*reserves;
	char			*temp;
	char			buf[BUFFER_SIZE];
	size_t			readc;

	if (!reserves)
	{
		reserves = (char*)malloc(sizeof(char));
		reserves[0] = '\0';
	}
	printf("\t\\N RESI _%d_%s_\n", ft_strchr(reserves, '\n'), reserves);
	readc = 1;
	while (readc && ft_strchr(reserves, '\n') == -1)
	{
		readc = read(fd, buf, BUFFER_SIZE - 1);
		buf[readc] = '\0';
		if (!readc)
		{
			reserves = ft_strjoin(reserves, buf);
			printf("\t\\0 RES _%d_%s_\n", ft_strchr(reserves, '\0'), reserves);
			break ;
		}
		temp = ft_strjoin(reserves, buf);
		free(reserves);
		reserves = temp;
		printf("\tREADC BUF _%zu_%s_\n", readc, buf);
		printf("\t\\N RES _%d_%s_\n", ft_strchr(reserves, '\n'), reserves);
	}
	if (ft_strchr(reserves, '\n') != -1)
		return (extract_line(&reserves, line, '\n'));
	else
		return (extract_line(&reserves, line, '\0'));
}
