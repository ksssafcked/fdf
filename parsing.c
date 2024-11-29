/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:04:04 by lsaiti            #+#    #+#             */
/*   Updated: 2024/11/29 17:42:13 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"


// void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!src)
// 		return (dest);
// 	while (i < n)
// 	{
// 		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
// 		i++;
// 	}
// 	return (dest);
// }

int	get_height(char	*file_name)
{
	int	i;
	int	fd;
	char	*str;
	
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		i++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (i);
}

void	*ft_realloc(void **ptr, size_t size)
{
	void	**new_ptr;
	int		i;

	new_ptr = malloc(size);
	if (!new_ptr)
		return (free(ptr), NULL);
	i = 0;
	while (ptr[i])
	{
		new_ptr[i] = ptr[i];
		free(ptr[i]);
		i++;
	}
	if (ptr)
		free(ptr);
	return (new_ptr);
}

char    **map_parser(char *file_name, int ***tab)
{
	char	**map;
	char	*str;
	int		fd;
	int		count;

	count = 0;
	fd = open(file_name, O_RDONLY);
	map = malloc(sizeof(char *) * (get_height(file_name) + 1));
	str = get_next_line(fd);
	while (str != NULL)
	{
		map[count] = str;
		str = get_next_line(fd);
		count++;
	}
	map[count] = NULL;
	*tab = malloc((count + 1) * sizeof(int *));
	close(fd);
	return (map);
}


void	free_str(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

map_utils	*map_parsing(char *file_name, map_utils *fdf)
{
	int		**map;
	char	**file;
	char	**line;
	int		i;
	int		j;

	file = map_parser(file_name, &map);
	j = 0;
	while (file[j])
	{
		line = ft_split(file[j], ' ');
		i = 0;
		while (line[i])
			i++;
		map[j] = malloc(i * sizeof(int));
		i = 0;
		while (line[i])
		{
			map[j][i] = ft_atoi(line[i]);
			i++;
		}
		free_str(line);
		j++;
	}
	free_str(file);
	map[j] = NULL;
	fdf->map = map;
	fdf->width = i;
	fdf->height = j;
	return (fdf);
}
