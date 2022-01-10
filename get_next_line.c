/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eanastas <eanastas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:06:54 by eanastas          #+#    #+#             */
/*   Updated: 2021/10/22 18:13:21 by eanastas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(const int fd)
{
	static char	*buffer[12288];
	int			next_line;
	int			i;

	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	malloc_buffer_if_needed(fd, &(buffer[fd]));
	next_line = -1;
	i = 0;
	while (next_line == -1 && i == 0)
	{
		next_line = check_for_next_line(buffer[fd]);
		if (next_line >= 0)
			return (prepare_return(&(buffer[fd]), next_line));
		else
			i = add_next_buffer(fd, &(buffer[fd]));
	}
	i = 0;
	while (buffer[fd][i] != '\0')
		++i;
	if (buffer[fd][0] != '\0')
		return (free_last_buffer(&(buffer[fd]), i));
	free(buffer[fd]);
	buffer[fd] = NULL;
	return (NULL);
}

void	malloc_buffer_if_needed(const int fd, char **buffer)
{
	if (!(*buffer))
	{
		(*buffer) = mal_buffer_and_read(fd, buffer[fd]);
		if (!(buffer))
			return ;
	}
}

char	*free_last_buffer(char **buffer, int len)
{
	char	*ret;
	int		i;

	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = (*buffer)[i];
		i++;
	}
	ret[i] = '\0';
	free (*buffer);
	*buffer = NULL;
	return (ret);
}

int	add_next_buffer(const int fd, char **buffer)
{
	int		len;
	char	*temp;
	int		temp_len;
	int		i;

	len = 0;
	while ((*buffer)[len] != '\0')
		len++;
	temp = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!temp)
		return (2);
	i = 0;
	while (i <= BUFF_SIZE)
		temp[i++] = '\0';
	if (read(fd, temp, BUFF_SIZE) <= 0)
	{
		free(temp);
		temp = NULL;
		return (1);
	}
	temp_len = 0;
	while (temp[temp_len] != '\0')
		temp_len++;
	add_buffers_together(len, temp_len, &(temp), &(*buffer));
	return (0);
}

void	add_buffers_together(int len, int temp_len, char **temp, char **buffer)
{
	char	*memory;
	int		i;
	int		j;

	memory = (char *)malloc(sizeof(char) * (len + temp_len + 1));
	if (!memory)
		return ;
	i = 0;
	while (i < len)
	{
		memory[i] = (*buffer)[i];
		i++;
	}
	j = 0;
	while (i < len + temp_len)
		memory[i++] = (*temp)[j++];
	memory[i] = '\0';
	free (*temp);
	*temp = NULL;
	free (*buffer);
	*buffer = memory;
	return ;
}

// int main(void)
// {
// 	// int fd = open("test", O_RDONLY); O_RDWR
// 	// int fd2 = open(0, O_RDONLY);
// 	printf("file #1: \n");
// 	int i = 1;
// 	char *print = get_next_line(fd2);
// 	while (i++ < 20)
// 	{
// 		printf("#%s", print);
// 		free (print);
// 		print = get_next_line(fd2);
// 	}
// 	free (print);
// 	print = NULL;
// 	i = 1;
// 	// printf("file #2 -> \n");
// 	// while (i++ < 10)
// 	// 	printf("%s -- line #%d\n", get_next_line(fd2), i - 1);
// 	return (0);
// }

// int main()
// {
// 	int fd0;
// 	fd0 = open("/dev/stdin", O_RDONLY);
// 	int i;
// 	i = 0;
// 	char **str = malloc(800);
// 	while(i < 10)
// 	{
// 		*(str + i) = get_next_line(fd0);
// 		i++;
// 	}
// 	while(*str)
// 	{
// 		printf("%s",*str);
// 		str++;
// 	}
// 	printf("%s",*str);
// 	close (fd0);
// 	return (0);
// }
