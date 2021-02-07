/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 10:53:47 by abahmani          #+#    #+#             */
/*   Updated: 2021/02/07 13:59:53 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	int		newline;
	//char	*tmp;

	if (ret == -1)
		return (-1);
	//tmp = *str;
	newline = find_new_line(*str);
	if (newline < 0)
	{
		*line = *str;
		*str = NULL;
		return (0);
	}
	else
	{
		*line = ft_substr(*str, 0, newline, 1);
		*str = ft_substr(*str, newline + 1, ft_strlen(*str) - newline, 0);
	/*	if (tmp)
			free(tmp);*/
		return (1);
	}
}
#include <stdio.h>
int				fill_buf(char *buf, char **line, char **str, int ret)
{
	int		newline;
	//char	*tmp;
//	static int i = 0;
//	printf("Occurence %i\n", i);
	buf[ret] = '\0';
	//tmp = *str;
	if (ret == -1)
		return (-1);
	newline = find_new_line(buf);
	if (newline > -1)
	{
	//	printf("(avant) %s\n", *str);
		*str = ft_strjoin(*str, buf);
	//	printf("(apres) %s\n", *str);
	//	i++;
	//	free(tmp);
		//tmp = *str;
		newline = find_new_line(*str);
		*line = ft_substr(*str, 0, newline, 1);
		*str = ft_substr(*str, newline + 1, ft_strlen(*str) - newline, 0);
		/*if (tmp)
			free(tmp);*/
		return (1);
	}
	*str = ft_strjoin(*str, buf);
//	if (tmp)
//		free(tmp);
//	printf("a\n");
	return (0);
}

int				free_str(int newline, char **str)
{
	if (newline == -1)
	{
		if (*str)
			free(*str);
//		if (str)
//			free(str);
//(void)str;
		return (-1);
	}
	return (newline);
}

int				get_next_line(int fd, char **line)
{
	int				ret;
	char			buf[BUFFER_SIZE + 1];
	static char		*str;
	int				newline;

	if (!line || BUFFER_SIZE <= 0 || read(fd, buf, 0))
		return (-1);
	if (!str)
	{
	//	printf("malloc\n");
		str = malloc(sizeof(char));
		str[0] = '\0';
	}
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		newline = fill_buf(buf, line, &str, ret);
		if (newline == 1 || newline == -1)
			return (free_str(newline, &str));
			//return (newline);
	}
	newline = end(ret, &str, line);
	return (free_str(newline, &str));
//	return (newline);
}
