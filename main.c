/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:40:46 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/03 20:47:42 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"
#include <math.h>

#define LARGEUR 2400

#define HAUTEUR 1500

int	get_x(int x, int y, map_utils *fdf)
{
	// double	i;
	double far;

	far = (LARGEUR * 0.5) / fdf->width;
	x = (x + 1) * far;
	y = (y + 1) * far;
	x = (y - x) * cos(0.523599);
	x += (LARGEUR - fdf->width) / 2;
	return (int)(x);
}

int	get_y(int x, int y, int z, map_utils *fdf)
{
	// double	i;
	double far;

	far = (HAUTEUR * 0.5) / fdf->height;
	x = (x + 1) * far;
	y = (y + 1) * far;
	y = (x + y) * sin(0.523599) - z;
	y += (HAUTEUR - fdf->height) / 2;
	return (int)(y);
}


// void draw_line(map_utils *fdf, t_point start, t_point end) {
//     int dx = abs(end.x - start.x);
//     int dy = abs(end.y - start.y);
//     int sx = (start.x < end.x) ? 1 : -1;
//     int sy = (start.y < end.y) ? 1 : -1;
//     int err = dx - dy;

//     while (1) {
// 		mlx_pixel_put(fdf->mlx, fdf->window, start.x, start.y, start.color);
//         if (start.x == end.x && start.y == end.y)
//             break;
//         int e2 = err * 2;
//         if (e2 > -dy) {
//             err -= dy;
//             start.x += sx;
//         }
//         if (e2 < dx) {
//             err += dx;
//             start.y += sy;
//         }
//     }
// }

void put_pixel_to_image(char *data, int x, int y, int color, int size_line, int bpp)
{
    if (x >= 0 && y >= 0 && x < LARGEUR && y < HAUTEUR) {
        int pixel_index = (y * size_line) + (x * (bpp / 8));
        data[pixel_index] = color & 0xFF;          // Bleu
        data[pixel_index + 1] = (color >> 8) & 0xFF; // Vert
        data[pixel_index + 2] = (color >> 16) & 0xFF; // Rouge
    }
}

void draw_line(map_utils *fdf, t_point start, t_point end)
{
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);
    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        put_pixel_to_image(fdf->img_data, start.x, start.y, start.color, fdf->size_line, fdf->bpp);
        if (start.x == end.x && start.y == end.y)
            break;
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            start.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            start.y += sy;
        }
    }
}

int ft_atoi_hex(char *hex_array) {
    int result = 0;
    int value = 0;

    while (*hex_array) {
        char c = *hex_array;

        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            value = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            value = c - 'A' + 10;
        }
        result = (result << 4) | value;
        hex_array++;
    }

    return result;
}


t_point rotate(map_utils *fdf, int i, int j, char *str)
{
	t_point p;
	char **str_tab;
	
	str_tab = ft_split(str, ',');
	if (str_tab[1])
		p.color = ft_atoi_hex(str_tab[1]);
	else
		p.color = 0xFFFFFF;
	p.x = i * fdf->far;
	p.y = j * fdf->far;
	p.z = ft_atoi(str_tab[0]);
	p.z *= (fdf->far);
	free_str(str_tab);
	return (p);
}

t_point	rotate_x(t_point p, double angle)
{
	int temp;	

	temp = p.y;
	p.y = (cos(angle) * temp) + (-sin(angle) * p.z);
	p.z = (sin(angle) * temp) + (cos(angle) * p.z);
	return (p);
}

t_point	rotate_y(t_point p, double angle)
{
	int temp;	

	temp = p.x;
	p.x = (cos(angle) * temp) + (sin(angle) * p.z);
	p.z = (sin(angle) * temp) + (cos(angle) * p.z);
	return (p);
}

t_point	rotate_z(t_point p, double angle)
{
	int	temp;

	temp = p.x;
	p.x = (cos(angle) * temp) + (-sin(angle) * p.y);
	p.y = (sin(angle) * temp) + (cos(angle) * p.y);
	return (p);
}

t_point	get_pos(map_utils *f, int i, int j, char *str)
{
	t_point	p;
	double angle;
	
	f->far = (HAUTEUR * 0.7) / f->height;

	p = rotate(f, i, j, str);
	angle = asin(1 / sqrt(3));
	p = rotate_x(p, angle);
	p = rotate_y(p, 0.785398);
	// p = rotate_z(p, 0.35);
	// p.x += (LARGEUR - (f->width * f->far)) / 2;
	// p.y += (HAUTEUR - (f->height * f->far))/ 2;
	return (p);
}


int	get_color(int a, int b)
{
	(void)b;
	if (a <= 0 )
		return (255);
	else
		return (16711935);
	
}

// void	draw_map(map_utils	*fdf)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < fdf->height)
// 	{
// 		j = 0;
// 		while (j < fdf->width)
// 		{
// 			if (j < fdf->width - 1)
// 				draw_line(fdf, fdf->point[i][j], fdf->point[i][j + 1]);
// 			if (i < fdf->height - 1)
// 				draw_line(fdf, fdf->point[i][j], fdf->point[i + 1][j]);
// 			j++;
// 		}
// 		i++;
// 	}
// }


void draw_map(map_utils *fdf)
{
    int i; 
	int	j;

    i = 0;
    while (i < fdf->height) 
	{
        j = 0;
        while (j < fdf->width) 
		{
            if (j < fdf->width - 1)
                draw_line(fdf, fdf->point[i][j], fdf->point[i][j + 1]);
            if (i < fdf->height - 1)
                draw_line(fdf, fdf->point[i][j], fdf->point[i + 1][j]);
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

int handle_key(int keycode, map_utils *fdf)
{
    if (keycode == 65307)
    {
		// free_fdf(fdf);
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
	if (!fdf)
		exit (0);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
	{
		free(fdf);
		exit (0);
	}
	fdf = map_parsing("./test_maps/42.fdf", fdf);
	if (!fdf->point)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf);
		exit (0);
	}
	fdf->window = mlx_new_window(fdf->mlx, LARGEUR, HAUTEUR, "Fil de Fer");
	if (!fdf->window)
	{
		mlx_destroy_display(fdf->mlx);
		free_fdf(fdf);
		free(fdf);
		exit (0);
	}
	return (fdf);
}

int main(void)
{
	map_utils	*fdf;

	fdf = map_init();
	fdf->img = mlx_new_image(fdf->mlx, LARGEUR, HAUTEUR);
    fdf->img_data = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->size_line, &fdf->endian);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
	mlx_key_hook(fdf->window, &handle_key, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
