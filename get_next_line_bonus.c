/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 13:08:34 by averheij       #+#    #+#                */
/*   Updated: 2019/12/16 14:17:51 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

/*
** 1 : A line has been read
** 0 : EOF has been reached 
** -1 : An error happened
*/

int		freemachin(t_file **head, t_file *file, int ret)
{
	t_file			*ptr;

	free(file->raw);
	file->raw = NULL;
	if (*head == file)
		*head = file->next;
	else
	{
		ptr = *head;
		while (ptr->next != file)
			ptr = ptr->next;
		ptr->next = file->next;
	}
	free(file);
	file = NULL;
	return (ret);
}

int		extract_line(t_file **head, t_file *file, char **line, int c)
{
	char			*temp;

	*line = ft_substr(file, 0, ft_strchr(file, c));
	if (!*line)
		return (freemachin(head, file, -1));
	if (c == '\0')
		return (freemachin(head, file, 0));
	temp = ft_substr(file, ft_strchr(file, c) + 1,
		file->len - ft_strchr(file, c));
	if (!temp)
		return (freemachin(head, file, -1));
	free(file->raw);
	file->len -= ft_strchr(file, c) + 1;
	file->raw = temp;
	return (1);
}

t_file	*new_file(t_file **node, int inputfd)
{
	t_file		*newfile;

	newfile = (t_file *)malloc(sizeof(t_file));
	if (!newfile)
		return (NULL);
	newfile->raw = (char *)malloc(sizeof(char));
	if (!newfile->raw)
	{
		free(newfile);
		return (NULL);
	}
	*node = newfile;
	newfile->len = 0;
	newfile->fd = inputfd;
	newfile->next = NULL;
	newfile->raw[0] = '\0';
	return (newfile);
}

t_file	*get_file(t_file **head, t_file *node, int inputfd)
{
	if (!*head)
		return (new_file(head, inputfd));
	else if (node->fd == inputfd)
		return (node);
	else if (node->next)
		return (get_file(head, node->next, inputfd));
	else
		return (new_file(&node->next, inputfd));
}

int		get_next_line(int fd, char **line)
{
	static t_file	*head;
	t_file			*file;
	ssize_t			readc;
	char			*temp;
	char			buf[BUFFER_SIZE + 1];

	file = get_file(&head, head, fd);
	if (BUFFER_SIZE < 0 || read(fd, 0, 0) == -1 || !file || !line)
		return (-1);
	readc = 1;
	while (readc && ft_strchr(file, '\n') == -1)
	{
		readc = read(file->fd, buf, BUFFER_SIZE);
		if (readc == -1)
			return (freemachin(&head, file, -1));
		buf[readc] = '\0';
		temp = ft_strjoin(file, buf, readc);
		if (!temp)
			return (freemachin(&head, file, -1));
		file->len += readc;
		free(file->raw);
		file->raw = temp;
	}
	return (extract_line(&head, file, line, ((readc) ? '\n' : '\0')));
}
