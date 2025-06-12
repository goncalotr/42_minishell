/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:21:16 by goteixei          #+#    #+#             */
/*   Updated: 2024/12/22 19:17:21 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_next(char *buffer)
{
	int		buffer_i;
	int		line_i;
	char	*line;

	buffer_i = 0;
	line_i = 0;
	if (!buffer)
		return (free(buffer), NULL);
	while (buffer[buffer_i] && buffer[buffer_i] != '\n')
		buffer_i++;
	if (!buffer[buffer_i])
	{
		free(buffer);
		return (NULL);
	}
	line = (char *)malloc((ft_strlen(buffer) - buffer_i + 1) * sizeof(char));
	if (!line)
		return (free(buffer), NULL);
	buffer_i++;
	while (buffer[buffer_i])
	{
		line[line_i++] = buffer[buffer_i++];
	}
	line[line_i] = '\0';
	return (free(buffer), line);
}

static char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (free(buffer), NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)malloc(i + 2 * sizeof(char));
	if (!line)
		return (free(buffer), NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	if (!res)
		res = ft_calloc (1, 1);
	if (!res)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (free(buffer), NULL);
	byte_read = 1;
	while (!ft_strchr(res, '\n') && byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(buffer), free(res), NULL);
		buffer[byte_read] = '\0';
		res = ft_strjoin(res, buffer);
		if (!res)
			return (free(buffer), NULL);
	}
	free (buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	if (buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_line(buffer);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	buffer = ft_next(buffer);
	return (line);
}

/* 
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>
# include <stdio.h>

int	main(void)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open("test.txt", O_RDONLY);
	//fd = 0;
	//fd = -1;
	if (fd == -1)
	{
		printf("Error opening file.");
		return (1);
	}

	printf("------------------------------------------");
	printf("\nStart of file reached or error occurred.\n\n");

	while (1)
	//while (count < 4)
	//while (line != NULL) //does this make the program not work
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("\nEnd of file reached or error occurred.\n");
			printf("------------------------------------------");
			break ;
		}
		count++;
		printf("[%d]: %s\n", count, line);
		free(line);
		line = NULL;
		
	}
	close (fd);
	return (0);
} */
