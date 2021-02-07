/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:15:40 by abahmani          #+#    #+#             */
/*   Updated: 2021/01/31 12:26:09 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "gnl_code/get_next_line.h"
#include <stdio.h>
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

static char	*ft_malloc(unsigned int start, size_t len, size_t size)
{
	char	*ptr;

	if (size > start)
	{
		if ((size_t)(size - start + 1) < len)
			ptr = malloc((size - start + 1) * sizeof(char));
		else
			ptr = malloc((len + 1) * sizeof(char));
	}
	else
		ptr = malloc(sizeof(char));
	return (ptr);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	char	*ptr;

	size = ft_strlen(s);
	i = 0;
	if (!s)
		return (0);
	ptr = ft_malloc(start, len, size);
	if (!ptr)
		return (NULL);
	while (start + i < size && s[start + i] && i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static	char	*concat(char const *src, char *dest, size_t start)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[start + i] = src[i];
		i++;
	}
	dest[start + i] = '\0';
	return (dest);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	return (concat(s2, concat(s1, str, 0), s1_len));
}

unsigned int	count_newline(char *buf)
{
	unsigned int i;
	unsigned int count;

	i = 0;
	count = 0;
	while (buf[i++])
		count++;
	return (count);
}

int				find_new_line(char *str)
{
	unsigned int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i])
		return (i);
	else
		return (-1);
}

int				end(int ret, char **str, char **line)
{
	int				newline;
	unsigned int	countline;

	if (ret == -1)
		return (-1);
	newline = find_new_line(*str);
	countline = count_newline(*str);
	if (countline > 1)
	{
		*line = ft_substr(*str, 0, newline + 1);
		*str = ft_substr(*str, newline + 1, ft_strlen(*str) - newline);
		return (1);
	}
	if (countline == 1)
	{
		*line = ft_substr(*str, 0, newline + 1);
		free(*str);
		*str = NULL;
		return (0);
	}
	return (0);
}

int				fill_buf(char *buf, char **line, char **str, int ret)
{
	int newline;

	buf[ret] = '\0';
	if (ret == -1)
		return (-1);
	newline = find_new_line(buf);
	if (newline > -1)
	{
		*str = ft_strjoin(*str, buf);
		newline = find_new_line(*str);
		*line = ft_substr(*str, 0, newline + 1);
		*str = ft_substr(*str, newline + 1, ft_strlen(*str) - newline);
		return (1);
	}
	*str = ft_strjoin(*str, buf);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	int				ret;
	char			buf[BUFFER_SIZE + 1];
	static char		*str;
	int				newline;

	if (!line || BUFFER_SIZE <= 0 || fd < 0)
		return (-1);
	if (!str)
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
	}
	if (fd == -1)
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		newline = fill_buf(buf, line, &str, ret);
		if (newline == 1 || newline == -1)
			return (newline);
	}
	return (end(ret, &str, line));
}

/*unsigned int	count_newline(char *buf)
{
	unsigned int i;
	unsigned int count;

	i = 0;
	count = 0;
	while (buf[i++])
		count++;
	return (count);
}

int	find_new_line(char *str)
{
	unsigned int i = 0;

	while (str[i] && str[i] != '\n')
		i++;
	if (str[i])
		return (i);
	else
		return (-1);
}

//int	fill_stri()

int	end(int ret, char **str, char **line)
{
	int				newline;
	unsigned int	countline;

	if (ret == -1)
		return (-1);
	newline = find_new_line(*str);
	countline = count_newline(*str);
	if (countline > 1)
	{
			*line = ft_substr(*str, 0, newline + 1);
			//printf("*line3 = %s\n", *line);
			*str = ft_substr(*str, newline + 1, ft_strlen(*str) - newline);
			//printf("*str = %s\n", *str);
			return (1);	
	}
	if (countline == 1)
	{
		*line = ft_substr(*str, 0, newline + 1);
		//printf("*line4 = %s\n", *line);
		free(*str);
		*str = NULL;
		return (0);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int				ret;
	char			buf[BUFFER_SIZE + 1];
	static char		*str;
	int			newline;
	//static int		t = 0;

	//t++;
	//printf("str0 = %s\n", str);
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (!str)
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
	}
	if (fd == -1)
		return (-1);
	newline = find_new_line(str);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		//printf("buf1 = %s\n", buf);
		if (ret == -1)
			return (-1);
		newline = find_new_line(buf);
		if (newline > -1)
		{
			str = ft_strjoin(str, buf);
			//printf("str2 = %s\n", str);
			newline = find_new_line(str);
			*line = ft_substr(str, 0, newline + 1);
			//printf("*line2 = %s\n", *line);
			str = ft_substr(str, newline + 1, ft_strlen(str) - newline);
			//printf("str3 = %s\n", str);
			return (1);
			}
		else
		{
			//printf("str avant join = %s\n", str);
			str = ft_strjoin(str, buf);
			//printf("str4 = %s\n", str);
		}
	}
	//str = ft_strjoin(str, buf);
	//printf("str5 = %s\n", str);
	return (end(ret, &str, line));
}
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//int main(int argc, char **argv)
int main (void)
{
	char *line;
	int fd = open("test.txt", O_RDONLY);
	//printf("%d\n", get_next_line(fd, &line));
	while (get_next_line(fd, &line) > 0)
	//for (int i = 0; i < 5; i++)
	{
		//printf("///////////////////////iteration numero %i//////////////////////////////////\n", i);
		//printf("return = %i\n", get_next_line(fd, &line));
		//get_next_line(fd, &line);
		printf("%s", line);
		//printf("return = %i\n", get_next_line(fd, &line));
	}
	return (0);
}
