/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 13:08:30 by averheij       #+#    #+#                */
/*   Updated: 2019/11/28 12:49:28 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif

int					get_next_line(int fd, char **line);
int					read_line(char **persistent, int fd);
int					extract_line(char **persistent, char **line, int c);
int					ft_strchr(char *s, int c);
int					ft_strrchr(char *s, int c);
char				*ft_strdup(const char *src);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_substr(char *s, unsigned int start, size_t len);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
#endif
