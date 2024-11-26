/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:40:46 by lsaiti            #+#    #+#             */
/*   Updated: 2024/11/26 17:12:08 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"
#include <math.h>

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

// int get_x(int x, int y)
// {
//     // Projette x et y en isométrique
//     double iso_x = (sqrt(2.0) / 2.0) * (x - y);
//     // Centre l'axe X sur l'écran
//     return (int)((iso_x * (HAUTEUR / 2)) / 19.0 + (HAUTEUR / 2));
// }

// int get_y(int x, int y, int z)
// {
//     // Projette x, y et z en isométrique
//     double factor1 = sqrt(2.0 / 3.0);
//     double factor2 = 1.0 / sqrt(6.0);
//     double iso_y = (factor1 * z) - (factor2 * (x + y));
//     // Centre l'axe Y sur l'écran
//     return (int)((iso_y * (LARGEUR / 2)) / 11.0 + (LARGEUR / 2));
// }

// int get_x(int x, int y)
// {
//     // Projette x et y en isométrique
//     double iso_x = (sqrt(2.0) / 2.0) * (x - y);
//     // Centre l'axe X sur l'écran
//     return (abs((int)iso_x));
// }

// int get_y(int x, int y, int z)
// {
//     // Projette x, y et z en isométrique
//     double factor1 = sqrt(2.0 / 3.0);
//     double factor2 = 1.0 / sqrt(6.0);
//     double iso_y = (factor1 * z) - (factor2 * (x + y));
//     // Centre l'axe Y sur l'écran
//     return (abs((int)iso_y));
// }

int get_x(int x, int y)
{
	double	i;

	i = ((sqrt(2) / 2) * (x - y));
	i *= -1;
	i = (i * (HAUTEUR / 2))/ 19;
	i += HAUTEUR / 2;
	return (int)(i);
}

int	get_y(int x, int y, int z)
{
	double	i;
	
	i = ((sqrt(2 / 3) * z) - ((1 / sqrt(6))* (x + y)));
	i *= -1;
	i = (i * (LARGEUR / 2)) / 11;
	i += LARGEUR / 2;
	return (int)(i);
}

void	draw_map(void *mlx, void *wint_ptr, int **map)
{
	int i;
	int j;

	i = 0;
	while (i < 11)
	{
		j = 0;
		while (j < 19)
		{
			if (map[i][j] == 0)
			{
				printf("%d, %d\n", get_x(i - 10, j - 5), get_y(i - 10, j - 5, 0));
				mlx_pixel_put(mlx, wint_ptr, get_x(i - 10, j - 5), get_y(i - 10,j - 5, 0), 0xFFFFFF);
			}
			else
			{
				printf("??%d, %d??\n", get_x(i - 10, j - 5), get_y(i - 10, j - 5, map[i][j]));
				printf("??%d, %d??\n", get_x(i - 10, j - 5), get_y(i - 10, j - 5, 0));
				mlx_pixel_put(mlx, wint_ptr, get_x(i - 10, j - 5) , get_y(i - 10, j - 5, map[i][j]), 0xFF0000);
			}
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
// (HAUTEUR / 2)* (1 + ( ((j * f) / 10) / (19)))