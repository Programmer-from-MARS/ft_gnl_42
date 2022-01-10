/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eanastas <eanastas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:06:58 by eanastas          #+#    #+#             */
/*   Updated: 2021/10/22 18:08:31 by eanastas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFF_SIZE 42

char	*get_next_line(const int fd);
int		add_next_buffer(const int fd, char **buffer);
void	prepare_memory_we_keep(int buffer_len, int ret_len, char **buffer);
int		check_for_next_line(char *buffer);
char	*mal_buffer_and_read(const int fd, char *buffer);
char	*prepare_return(char **buffer, int next_line);
int		add_next_buffer(const int fd, char **buffer);
void	add_buffers_together(int len, int temp_len, char **temp, char **buffer);
char	*free_last_buffer(char **buffer, int len);
void	malloc_buffer_if_needed(const int fd, char **buffer);

#endif