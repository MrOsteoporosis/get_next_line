/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 13:08:34 by averheij       #+#    #+#                */
/*   Updated: 2019/11/28 15:23:50 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

/*
** 1 : A line has been read
** 0 : EOF has been reached
** -1 : An error happened
*/

char		*ft_strjoin(t_file *file, char *str, int readc)//Done
{
	char	*res;
	int		i;

	if (!file->raw || !str)
		return (NULL);
	res = (char*)malloc(sizeof(char) * (file->len + readc + 1));
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

int		extract_line(t_file *file, char **line, int c)//Done
{
	char			*temp;

	printf("\tCHR _%d_%d_\n", c, ft_strchr(*persistent, c));
	printf("\tRES _%d_%s_\n", ft_strchr(*persistent, '\n'), *persistent);
	*line = ft_substr(file, 0, ft_strchr(file, c));
	printf("\tLINE _%s_\n", *line);
	if (c == '\0')
	{
		perror("EOF free res");
		free(file->raw);
		file->raw = NULL;
		return (0);
	}
	temp = ft_substr(file, ft_strchr(file, c) + 1,
		file->len - ft_strchr(file, c)); 
	//Shorten length as needed
	free(file->raw);
	file->raw = temp;
	printf("\tRESF _%d_%s_\n", ft_strchr(*persistent, '\n'), *persistent);
	return (1);
}

void	read_line(t_file *file)//Done
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
		printf("\t\\N RES _%d_%s_\n", ft_strchr(*persistent, '\n'), *persistent);
	}
}

int		get_next_line(int fd, char **line)//Done
{
	static t_file	persistent;//Struct
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
	printf("\t\\N RESI _%d_%s_\n", ft_strchr(persistent, '\n'), persistent);
	read_line(file);
	perror("Extracting");
	if (ft_strchr(file, '\n') != -1)//Pass variable//Pass struct to use readc length
		return (extract_line(file, line, '\n'));//Whole struct
	else
		return (extract_line(file, line, '\0'));//Whole struct
}

t_file	*get_file(t_file *persistent, int inputfd)//Done
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