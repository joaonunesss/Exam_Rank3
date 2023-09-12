#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}

int	ft_strchr(char *temp)
{
	int	i = 0;

	if (!temp)
		return (1);
	while (temp[i])
	{
		if (temp[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*strjoin(char *temp, char *buffer)
{
	int		i = -1;
	int		j = 0;
	char	*strjoin;

	if (!temp)
	{
		temp = malloc(1);
		temp[0] = '\0';
	}
	strjoin = malloc(ft_strlen(temp) + ft_strlen(buffer) + 1);
	if (!strjoin)
		return (NULL);
	while (temp[++i])
		strjoin[i] = temp[i];
	while (buffer[j])
		strjoin[i++] = buffer[j++];
	strjoin[i] = '\0';
	free(temp);
	return (strjoin);
}

char	*get_line(char *temp)
{
	int		i = 0;
	char	*line;

	if (!temp[i])
		return (NULL);
	while (temp[i] && temp[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
	{
		line[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*clean_temp(char *temp)
{
	int		i;
	int		j;
	char	*clean;

	i = 0;
	j = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\0')
	{
		free(temp);
		return (NULL);
	}
	clean = malloc(ft_strlen(temp) - i + 1);
	if (!clean)
		return (NULL);
	i++;
	while (temp[i])
		clean[j++] = temp[i++];
	clean[j] = '\0';
	free(temp);
	return (clean);
}

char	*get_next_line(int fd)
{
	char		*line, *buffer;
	static char	*temp;
    int		bytes_read = 1;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
    buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (ft_strchr(temp) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(temp);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (!buffer)
			return (NULL);
		temp = strjoin(temp, buffer);
	}
	free(buffer);
	if (!temp)
		return (NULL);
	line = get_line(temp);
	temp = clean_temp(temp);
	return (line);
}

// int main()
// {
//     int fd = 0;

//     fd = open("text.txt", O_RDONLY);
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     close(fd);
// }
