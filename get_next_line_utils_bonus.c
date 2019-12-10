/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 13:08:25 by averheij       #+#    #+#                */
/*   Updated: 2019/12/10 13:10:50 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

int		ft_strchr(t_file *f, int c)
{
	size_t	i;

	i = 0;
	while (i < f->len)
	{
		if (f->raw[i] == c)
			return (i);
		i++;
	}
	if (!c)
		return (i);
	return (-1);
}

char	*ft_substr(t_file *f, unsigned int start, size_t sublen)
{
	char	*sub;

	if (!f->raw)
		return (NULL);
	if (f->len < start)
		return (ft_strdup(""));
	sub = (char *)malloc(sizeof(char) *
		(((f->len - start < sublen) ? f->len - start : sublen) + 1));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, f->raw + start,
		((f->len - start < sublen) ? f->len - start : sublen) + 1);
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

char	*ft_strjoin(t_file *file, char *str, size_t readc)
{
	char	*res;
	size_t	i;

	if (!file->raw || !str)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (file->len + readc + 1));
	if (!res)
		return (NULL);
	res[file->len + readc] = '\0';
	i = 0;
	while (i < file->len || i < readc)
	{
		if (i < file->len)
			res[i] = file->raw[i];
		if (i < readc)
			res[i + file->len] = str[i];
		i++;
	}
	return (res);
}
