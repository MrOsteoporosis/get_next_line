/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 13:08:34 by averheij       #+#    #+#                */
/*   Updated: 2019/12/10 13:10:57 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
** 1 : A line has been read
** 0 : EOF has been reached
** -1 : An error happened
*/

int		freemachin(t_file **persistent, t_file *file)
{
	t_file			*ptr;

	free(file->raw);
	file->raw = NULL;
	if (*persistent == file)
		*persistent = file->next;
	else
	{
		ptr = *persistent;
		while (ptr->next != file)
			ptr = ptr->next;
		ptr->next = file->next;
	}
	free(file);
	file = NULL;
	return (0);
}

int		extract_line(t_file **persistent, t_file *file, char **line, int c)
{
	char			*temp;

	if (line)
		free(*line);
	*line = ft_substr(file, 0, ft_strchr(file, c));
	if (c == '\0')
		return (freemachin(persistent, file));
	temp = ft_substr(file, ft_strchr(file, c) + 1,
		file->len - ft_strchr(file, c));
	file->len -= ft_strchr(file, c) + 1;
	free(file->raw);
	file->raw = temp;
	return (1);
}

void	read_line(t_file *file)
{
	size_t		readc;
	char		*temp;
	char		buf[BUFFER_SIZE + 1];

	readc = 1;
	while (readc && ft_strchr(file, '\n') == -1)
	{
		readc = read(file->fd, buf, BUFFER_SIZE);
		buf[readc] = '\0';
		temp = ft_strjoin(file, buf, readc);
		file->len += readc;
		free(file->raw);
		file->raw = temp;
	}
}

t_file	*get_file(t_file **dontuseme, int inputfd)
{
	t_file		*newfile;
	t_file		*persistent;

	persistent = *dontuseme;
	while (persistent && persistent->next)
	{
		if (persistent->fd == inputfd)
			return (persistent);
		persistent = persistent->next;
	}
	if (persistent && persistent->fd == inputfd)
		return (persistent);
	newfile = (t_file *)malloc(sizeof(t_file));
	if (*dontuseme)
		persistent->next = newfile;
	else
		*dontuseme = newfile;
	newfile->len = 0;
	newfile->fd = inputfd;
	newfile->next = NULL;
	newfile->raw = (char *)malloc(sizeof(char));
	newfile->raw[0] = '\0';
	return (newfile);
}

int		get_next_line(int fd, char **line)
{
	static t_file	*persistent;
	t_file			*file;

	file = get_file(&persistent, fd);
	if (BUFFER_SIZE < 0 || read(fd, 0, 0) == -1)
		return (-1);
	read_line(file);
	if (ft_strchr(file, '\n') != -1)
		return (extract_line(&persistent, file, line, '\n'));
	else
		return (extract_line(&persistent, file, line, '\0'));
}
