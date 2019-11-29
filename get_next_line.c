/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 13:08:34 by averheij       #+#    #+#                */
/*   Updated: 2019/11/29 13:40:17 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

/*
** 1 : A line has been read
** 0 : EOF has been reached
** -1 : An error happened
*/

int		freemachin(t_file **persistent, t_file *file)
{
	t_file			*ptr;
	// perror("EOF free res");
	free(file->raw);
	file->raw = NULL;
	if (*persistent == file)
	{
		// perror("New First");
		*persistent = file->next; 
	}
	else
	{
		// perror("Link shift");
		ptr = *persistent;
		while (ptr->next != file)
			ptr = ptr->next;
		ptr->next = file->next;
	}
	// perror("Free Done");
	free(file);
	file = NULL;
	//Free struct and remove from list
	return (0);
}

int		extract_line(t_file **persistent, t_file *file, char **line, int c)
{
	char			*temp;

	// printf("\tRES _%d_%s_\n", ft_strchr(file, '\n'), file->raw);
	if (line && *line)
		free(*line);
	*line = ft_substr(file, 0, ft_strchr(file, c));
	// printf("\tLINE _%s_\n", *line);
	if (c == '\0')
		return (freemachin(persistent, file));
	temp = ft_substr(file, ft_strchr(file, c) + 1,
		file->len - ft_strchr(file, c)); 
	file->len -= ft_strchr(file, c) + 1;
	free(file->raw);
	file->raw = temp;
	// printf("\tRESF _%d_%zu_%s_\n", ft_strchr(file, '\n'), file->len, file->raw);
	return (1);
}

void	read_line(t_file *file)
{
	size_t		readc;
	char		*temp;
	char		buf[BUFFER_SIZE + 1];

	readc = 1;
	// perror("Start read");
	while (readc && ft_strchr(file, '\n') == -1)
	{
		readc = read(file->fd, buf, BUFFER_SIZE);
		buf[readc] = '\0';
		temp = ft_strjoin(file, buf, readc);
		file->len += readc;
		free(file->raw);
		file->raw = temp;
		// printf("\tREADC BUF _%zu_%s_\n", readc, buf);
		// printf("\t\\N RES _%d_%s_\n", ft_strchr(file, '\n'), file->raw);
	}
}

t_file	*get_file(t_file **dontuseme, int inputfd)
{
	t_file		*newfile;
	t_file		*persistent;

	persistent = *dontuseme;
	// printf("PERSIS_%p_\n", *persistent);
	// printf("FD IN_%d_\n", inputfd);
	while(persistent && persistent->next)
	{
		// printf("FD FILE_%d_\n", persistent)->fd);
		if (persistent->fd == inputfd)
			return persistent;
		persistent = persistent->next;
	}
	if (persistent)
		// printf("FD FILE_%d_\n", persistent)->fd);
	if (persistent && persistent->fd == inputfd)
			return (persistent);
	// perror("No File Found");
	newfile = (t_file*)malloc(sizeof(t_file));
	if (*dontuseme)
		persistent->next = newfile;
	else
		*dontuseme = newfile;
	newfile->len = 0;
	newfile->fd = inputfd;
	newfile->next = NULL;
	newfile->raw = (char*)malloc(sizeof(char));
	newfile->raw[0] = '\0';
	return (newfile);
}

int		get_next_line(int fd, char **line)
{
	static t_file	*persistent;
	t_file			*file;

	file = get_file(&persistent, fd);
	// if (!file->raw)
	// {
		// perror("persistent init");
	// 	file->raw = (char*)malloc(sizeof(char));
	// 	file->raw[0] = '\0';
	// }
	if (read(fd, 0, 0) == -1)
		return (-1);
	// printf("\t\\N RESI _%d_%s_\n", ft_strchr(file, '\n'), file->raw);
	read_line(file);
	// perror("Extracting");
	if (ft_strchr(file, '\n') != -1)
		return (extract_line(&persistent, file, line, '\n'));
	else
		return (extract_line(&persistent, file, line, '\0'));
}