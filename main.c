/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:40:46 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/03 16:10:47 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"
#include <math.h>

#define LARGEUR 2400

#define HAUTEUR 1500

/*int get_x(int x, int y, map_utils *fdf)
{
	double	i;
	double	far;

	far = (LARGEUR * 0.5) / fdf->width;
	i = ((sqrt(2) / 2) * (y - x));
	i *= far;
	i += LARGEUR * 0.5;
	return (int)(i);
}

int	get_y(int x, int y, int z, map_utils *fdf)
{
	double	i;
	double far;

	far = (HAUTEUR * 0.8) / fdf->height;
	i = ((1 / sqrt(6))* (x + y));
	i *= far;
	i += HAUTEUR * 0.2;
	i -= (sqrt((double)2 / 3) * z);
	return (int)(i);
}*/
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


void draw_line(map_utils *fdf, t_point *start, t_point *end, int color) {
    int dx = abs(end->x - start->x);
    int dy = abs(end->y - start->y);
    int sx = (start->x < end->x) ? 1 : -1;
    int sy = (start->y < end->y) ? 1 : -1;
    int err = dx - dy;

    while (1) {
		mlx_pixel_put(fdf->mlx, fdf->window, start->x, start->y, color);
        if (start->x == end->x && start->y == end->y)
            break;
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            start->x += sx;
        }
        if (e2 < dx) {
            err += dx;
            start->y += sy;
        }
    }
}

/*void	draw_map(map_utils *fdf) {
    int i, j;
    t_point start, end;
	int	color;

    for (i = 0; i < fdf->height; i++) {
        for (j = 0; j < fdf->width; j++) {
            start->x = get_x(i, j, fdf);
            start->y = get_y(i, j, fdf->map[i][j], fdf);
			if (fdf->map[i][j] == 0)
				color = 16777215;
			else
				color = 16711935;
            if (j < fdf->width - 1) {
                end->x = get_x(i, j + 1, fdf);
                end->y = get_y(i, j + 1, fdf->map[i][j + 1], fdf);
                draw_line(fdf, start, end, color);
            }
            if (i < fdf->height - 1) {
                end->x = get_x(i + 1, j, fdf);
                end->y = get_y(i + 1, j, fdf->map[i + 1][j], fdf);
                draw_line(fdf, start, end, color);
            }
        }
    }
}
*/

t_point *rotate(int i, int j, int k)
{
	t_point *p;

	p = malloc(sizeof(t_point));
	p->x = i;
	p->y = j;
	p->z = k;
	return (p);
}

/*t_point	*rotate_yy(int i, int j, int k)
{
	t_point	*p;
	double	angle = 3.14159;
	// (void)k;
	p = malloc(sizeof(t_point));
	p->x = (cos(angle) * i) + (sin(angle) * k);
	// p->x = i;
	p->y = j;
	p->z = (-sin(angle) * i) + (cos(angle) * k);
	return (p);
}*/
t_point	*rotate_x(t_point *p, double angle)
{
	int temp;	

	temp = p->y;
	p->y = (cos(angle) * temp) + (-sin(angle) * p->z);
	p->z = (sin(angle) * temp) + (cos(angle) * p->z);
	return (p);
}

t_point	*rotate_y(t_point *p, double angle)
{
	int temp;	

	temp = p->x;
	p->x = (cos(angle) * temp) + (sin(angle) * p->z);
	p->z = (sin(angle) * temp) + (cos(angle) * p->z);
	return (p);
}

t_point	*rotate_z(t_point *p, double angle)
{
	int	temp;

	temp = p->x;
	p->x = (cos(angle) * temp) + (-sin(angle) * p->y);
	p->y = (sin(angle) * temp) + (cos(angle) * p->y);
	return (p);
}

t_point	*get_pos(map_utils *f, int i, int j, int k)
{
	t_point	*p;
	int	far;
	// double	a = 0.52;
	// double b = 0.785398;
	// double b = 0.52;

	far = (LARGEUR * 0.7) / f->width;
	i *= far;
	j *= far;
	k *= (far / 19);
	// p->x = i;
	// p->y = j;
	// p->x = (cos(b) * i) + (-sin(b) * k);
	// p->x = (sqrt(3) / sqrt (6)) * i + (-(sqrt(3) / sqrt(6)) * k);
	
	// p->y = (1 /sqrt(6)) * i + (2 / sqrt(6)) * j + (1 / sqrt(6)) * k;
	// p->y = ((sin(a) * sin(b)) * i) + (cos(a) * j) + ((sin(a) * cos(b)) * k);
	// p->y += (HAUTEUR - f->height) / 2;
	// p->z = 0;

	p = rotate(i, j, k);
	/*

	/// final
	
	
	p = rotate_z(p, 0.785398);
	p = rotate_x(p, 0.09);
	p = rotate_y(p, 0.3);
	
	*/
	double angle = asin(1 / sqrt(3));
	p = rotate_x(p, angle);
	p = rotate_y(p, 0.785398);
	// p = rotate_y(p, -0.785398);
	// p = rotate_x(p, 0.52);
	// p = rotate_x(p, -0.610865238);
	
	// p = rotate_y(p, 3.14159);
	// p = rotate_y(p, 0.6);
	// p = rotate_x(p, 0.3);
	// p = rotate_x(p, -0.07);
	// p = rotate_y(p, -0.07);	
	// p = rotate_z(p, -0.785398);

	
	// p = rotate_y(p, 0.3);

	// p = rotate_y(p, 0.785398);
	// p = rotate_y(p, 2.44346);
	// p = rotate_z(p, 0.3);
	// p = rotate_z(p, -1.5);
	// p = rotate_y(p, -0.1);
	// p = rotate_x(p, );
	// p = rotate_y(p, 0.10);
	
	p->x += (LARGEUR - (f->width * far)) / 2;
	p->y += (HAUTEUR - (f->height * far))/ 2;
	// p->y += (HAUTEUR / 2);
	return (p);
}


int	get_color(int a, int b)
{
	if (a > b || a < b)
		return (16711935);
	return (16777215);
}

void	draw_map(map_utils	*fdf)
{
	int i;
	int j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width - 1)
		{
			if (j < fdf->width - 1 && fdf->map[i][j + 1] >= 10)
				draw_line(fdf, get_pos(fdf, j, i, fdf->map[i][j]), get_pos(fdf, j + 1, i, fdf->map[i][j + 1]), 16711935);
			else if (j < fdf->width -1)
				draw_line(fdf, get_pos(fdf, j, i, fdf->map[i][j]), get_pos(fdf, j + 1, i, fdf->map[i][j + 1]), 16777215);
			if (i < fdf->height - 1 && fdf->map[i + 1][j] >= 10)
                draw_line(fdf, get_pos(fdf, j, i, fdf->map[i][j]), get_pos(fdf,j,i + 1, fdf->map[i + 1][j]), 16711935);
            if (i < fdf->height - 1)
                draw_line(fdf, get_pos(fdf, j, i, fdf->map[i][j]), get_pos(fdf,j,i + 1, fdf->map[i + 1][j]), 16777215);
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
	if (!fdf)
		exit (0);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
	{
		free(fdf);
		exit (0);
	}
	fdf = map_parsing("./test_maps/42.fdf", fdf);
	if (!fdf->map)
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
	draw_map(fdf);
	mlx_key_hook(fdf->window, &handle_key, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
