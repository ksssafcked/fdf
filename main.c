/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:40:46 by lsaiti            #+#    #+#             */
/*   Updated: 2024/11/29 17:27:29 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"
#include <math.h>

#define LARGEUR 2400

#define HAUTEUR 1500

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

	i = ((sqrt(2) / 2) * (y - x));
	i *= 30;
	i += LARGEUR / 2;
	return (int)(i);
}

int	get_y(int x, int y, int z)
{
	double	i;

	i = ((1 / sqrt(6))* (x + y));
	i *= 30;
	i += HAUTEUR / 2;
	i -= (sqrt((double)2 / 3) * z);
	return (int)(i);
}

void	draw_map(map_utils	*fdf)
{
	int i;
	int j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (fdf->map[i][j] == 0)
			{
				// printf("%d, %d\n", get_x(i, j) + 200 + (10 * i), get_y(i, j, 0) + 200);
				mlx_pixel_put(fdf->mlx, fdf->window, get_x(i, j), get_y(i, j, 0), 0xFFFFFF);
			}
			else
			{
				// printf("??%d, %d??\n", get_x(i, j) + 200 + (10 * j), get_y(i, j, 10));
				// printf("??%d, %d??\n", get_x(i, j) + 200 + (10 * j), get_y(i, j, 0) + 200);
				mlx_pixel_put(fdf->mlx, fdf->window, get_x(i, j), get_y(i, j, fdf->map[i][j]), 0xFF00FF);
			}
			j++;
		}
		i++;
	}
}

void	free_fdf(map_utils *fdf)
{
	int	i;

	i = 0;
	while (fdf->map[i])
	{
		free(fdf->map[i]);
		i++;
	}
	free(fdf->map);
	fdf->map = NULL;
}


/*map_utils	*get_map_info(map_utils *fdf)
{
	int	i;

	i = 0;
	while (fdf->map[i])
		i++;
	fdf->width = i;
	fdf->height = 11;
	return (fdf);
}*/

int handle_key(int keycode, map_utils *fdf)
{
    if (keycode == 65307)
    {
		free_fdf(fdf);
        mlx_destroy_window(fdf->mlx, fdf->window);
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
		free(fdf);
		exit (0);
    }
    return (0);
}


map_utils	*map_init(void)
{
	map_utils	*fdf;
	
	fdf = malloc(sizeof(map_utils));
	fdf->mlx = mlx_init();
	fdf = map_parsing("./test_maps/42.fdf", fdf);
	fdf->window = mlx_new_window(fdf->mlx, LARGEUR, HAUTEUR, "Fil de Fer");
	return (fdf);
}

int main(void)
{
	map_utils	*fdf;

	fdf = map_init();
	draw_map(fdf);
	mlx_key_hook(fdf->window, &handle_key, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
