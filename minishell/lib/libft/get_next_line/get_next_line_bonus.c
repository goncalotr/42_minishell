/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:21:16 by goteixei          #+#    #+#             */
/*   Updated: 2024/12/23 10:54:30 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	if (buffer[fd][0] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = ft_line(buffer[fd]);
	if (!line)
		return (free(buffer[fd]), buffer[fd] = NULL, NULL);
	buffer[fd] = ft_next(buffer[fd]);
	return (line);
}

/*
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>
# include <stdio.h>

int	main(void)
{
	const char *files[] = {"file1.txt", "file2.txt", "file3.txt"};
	int num_files = sizeof(files) / sizeof(files[0]);
	int fds[num_files];
	int eof_flags[num_files];
	int line_counts[num_files];
	char *line;
	int i;
	int files_remaining;

	for (i = 0; i < num_files; i++)
	{
		fds[i] = open(files[i], O_RDONLY);
		if (fds[i] < 0)
		{
			perror("Error opening file");
			while (--i >= 0) close(fds[i]);
			return 0;
		}
		eof_flags[i] = 0;
		line_counts[i] = 0; 
	}

	files_remaining = num_files;

	printf("===== Testing get_next_line Bonus =====\n");

	while (files_remaining > 0)
	{
		for (i = 0; i < num_files; i++)
		{
			if (!eof_flags[i])
			{
				line = get_next_line(fds[i]);
				if (line)
				{
					line_counts[i]++;
					printf("File%d (Line %d): %s", i + 1, line_counts[i], line);
					if (line[ft_strlen(line) - 1] != '\n')
						printf("\n");
					free(line);
				}
				else
				{
					printf("File%d: (EOF)\n", i + 1);
					eof_flags[i] = 1;
					files_remaining--;
				}
			}
		}
	}

	for (i = 0; i < num_files; i++)
		close(fds[i]);

	printf("===== End of Test =====\n");
}
*/
