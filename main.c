/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:40:46 by lsaiti            #+#    #+#             */
/*   Updated: 2024/11/21 19:15:34 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"


#define HAUTEUR 1920

#define LARGEUR 1080

char    **map_parser(char *file_name)
{
	char	**map;
	char	*str;
	int		fd;
	int		count;

	count = 0;
	fd = open(file_name, O_RDONLY);
	map = malloc(40 * sizeof (char *));
	str = get_next_line(fd);
	while (str != NULL)
	{
		map[count] = str;
		str = get_next_line(fd);
		count++;
	}
	map[count] = NULL;
	return (map);
}

int	**map_parsing(char *file_name)
{
	int		**map;
	char	**file;
	char	**line;
	int		i;
	int		j;

	map = malloc(20 * sizeof(int *));
	file = map_parser(file_name);
	j = 0;
	while (*file)
	{
		map[j] = malloc(20 * sizeof(int));
		line = ft_split(*file, ' ');
		i = 0;
		while (*line)
		{
			map[j][i] = ft_atoi(*line);
			i++;
			line++;
		}
		j++;
		free(*file);
		file++;
	}
	return (map);
}

void	draw_map(void *mlx, void *wint_ptr, int **map)
{
	int i = 0;
	int j = 0;
	while (i < 11)
	{
		j = 0;
		while (j < 19)
		{
			if (map[i][j] == 0)
				mlx_pixel_put(mlx, wint_ptr, (j * HAUTEUR) / 19, (i * LARGEUR) / 11, 0xFFFFFF);
			else
				mlx_pixel_put(mlx, wint_ptr, (j * HAUTEUR) / 19, (i * LARGEUR) / 11, 0xFF0000);
			j++;
		}
		i++;
	}
}

int main(void)
{
	void    *mlx;
	void    *wint_ptr;
	int		**map;

	mlx = mlx_init();
	map = map_parsing("./test_maps/42.fdf");
	(void)map;
	wint_ptr = mlx_new_window(mlx, HAUTEUR, LARGEUR, "Yes");
	draw_map(mlx, wint_ptr, map);
	while (1)
	{
		
	}
}
