/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 13:08:25 by averheij       #+#    #+#                */
/*   Updated: 2020/01/07 13:44:01 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*cpy;
	int		l;
	int		i;

	l = 0;
	while (src[l])
		l++;
	cpy = (char *)malloc(l + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < l)
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

int		ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (!c)
		return (i);
	return (-1);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
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
	sub = (char *)malloc(sizeof(char) *
		((i - start < len) ? i - start : len) + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, ((i - start < len) ? i - start : len) + 1);
	return (sub);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int		i;

	if (!src)
		return (0);
	i = 0;
	while (src[i] && i < (int)dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < (int)dstsize)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		l1;
	int		l2;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strchr(s1, '\0');
	l2 = ft_strchr(s2, '\0');
	res = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
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
