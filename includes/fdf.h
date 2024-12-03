/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:09:38 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/03 20:22:36 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "mlx.h"
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_point {
    int x;
    int y;
	int	z;
	int color;
} t_point;

typedef struct map_utils{
	int		**map;
	t_point	**point;
	t_point	*start;
	int		height;
	int		width;
	void	*mlx;
	void	*window;
	void *img;
    char *img_data;
	int			bpp;
	int			size_line;
	int			endian;
	int	far;
}	map_utils;

int			ft_atoi(char *str);
void		*ft_freesplit(char **split, int nb);
int			count_words(const char *str, char charset);
char		*ft_word(const char *src, char charset);
void		*ft_splitchar(char **split, char const *s, char c);
char		**ft_split(char const *s, char c);
char    	**map_parser(char *file_name);
map_utils	*map_parsing(char *file_name, map_utils *fdf);
void		free_str(char	**str);
t_point	get_pos(map_utils *f, int i, int j, char *str);
