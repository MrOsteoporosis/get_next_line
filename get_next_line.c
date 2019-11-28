/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 13:08:34 by averheij       #+#    #+#                */
/*   Updated: 2019/11/28 15:36:54 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

/*
** 1 : A line has been read
** 0 : EOF has been reached
** -1 : An error happened
*/

int		extract_line(t_file *file, char **line, int c)
{
	char			*temp;

	printf("\tCHR _%d_%d_\n", c, ft_strchr(file, c));//Based on length
	printf("\tRES _%d_%s_\n", ft_strchr(file, '\n'), file->raw);
	*line = ft_substr(file, 0, ft_strchr(file, c));//This based on length
	printf("\tLINE _%s_\n", *line);
	if (c == '\0')
	{
		perror("EOF free res");
		free(file->raw);
		file->raw = NULL;
		//Free struct and remove from list
		return (0);
	}
	temp = ft_substr(file, ft_strchr(file, c) + 1,
		file->len - ft_strchr(file, c)); 
	//Shorten length as needed
	free(file->raw);
	file->raw = temp;
	printf("\tRESF _%d_%s_\n", ft_strchr(file, '\n'), file->raw);
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
		perror("Reading");
		readc = read(file->fd, buf, BUFFER_SIZE);
		buf[readc] = '\0';
		temp = ft_strjoin(file, buf, readc);
		file->len += readc;
		free(file->raw);
		file->raw = temp;
		printf("\tREADC BUF _%zu_%s_\n", readc, buf);
		printf("\t\\N RES _%d_%s_\n", ft_strchr(file, '\n'), file->raw);
	}
}

int		get_next_line(int fd, char **line)
{
	static t_file	persistent;
	t_file			*file;

	file = get_file(&persistent, fd);
	if (!file->raw)
	{
		perror("persistent init");
		file->raw = (char*)malloc(sizeof(char));
		file->raw[0] = '\0';
	}
	if (read(fd, 0, 0) == -1)
		return (-1);
	printf("\t\\N RESI _%d_%s_\n", ft_strchr(file, '\n'), file->raw);
	read_line(file);
	perror("Extracting");
	if (ft_strchr(file, '\n') != -1)
		return (extract_line(file, line, '\n'));
	else
		return (extract_line(file, line, '\0'));
}

t_file	*get_file(t_file *persistent, int inputfd)
{
	t_file		*newfile;

	newfile = (t_file*)malloc(sizeof(t_file));
	while(persistent->next)
	{
		if (persistent->fd == inputfd)
			return (persistent);
		persistent = persistent->next;
	}
	if (persistent->fd == inputfd)
			return (persistent);
	persistent->next = newfile;
	newfile->len = 0;
	newfile->fd = inputfd;
	newfile->next = NULL;
	return (newfile);
}