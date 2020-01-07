/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 13:08:30 by averheij       #+#    #+#                */
/*   Updated: 2020/01/07 13:45:19 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stddef.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif

typedef struct		s_file
{
	char			*raw;
	int				fd;
	struct s_file	*next;
}					t_file;

int					get_next_line(int fd, char **line);
t_file				*get_file(t_file **head, t_file *node, int inputfd);
t_file				*new_file(t_file **node, int inputfd);
int					extract_line(t_file **head, t_file *file, char **line,
						int c);
int					freemachin(t_file **head, t_file *file, int ret);
int					ft_strchr(char *s, int c);
char				*ft_strdup(const char *src);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_substr(char *s, unsigned int start, size_t len);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
#endif
