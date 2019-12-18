/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 13:08:30 by averheij       #+#    #+#                */
/*   Updated: 2019/12/18 13:30:48 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif

typedef struct		s_file
{
	char			*raw;
	size_t			len;
	int				fd;
	struct s_file	*next;
}					t_file;

int					get_next_line(int fd, char **line);
t_file				*get_file(t_file **head, t_file *node, int inputfd);
t_file				*new_file(t_file **node, int inputfd);
int					extract_line(t_file **head, t_file *file, char **line,
						int c);
int					freemachin(t_file **head, t_file *file, int ret);
int					ft_strchr(t_file *f, int c);
char				*ft_strdup(const char *src);
char				*ft_strjoin(t_file *file, char *str, size_t readc);
char				*ft_substr(t_file *f, unsigned int start, size_t sublen);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
#endif
