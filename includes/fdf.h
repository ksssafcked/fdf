/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:09:38 by lsaiti            #+#    #+#             */
/*   Updated: 2024/11/29 15:06:05 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "mlx.h"
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct map_utils{
	int		**map;
	int		**coordinate;
	int		height;
	int		width;
	void	*mlx;
	void	*window;
}	map_utils;

int			ft_atoi(char *str);
void		*ft_freesplit(char **split, int nb);
int			count_words(const char *str, char charset);
char		*ft_word(const char *src, char charset);
void		*ft_splitchar(char **split, char const *s, char c);
char		**ft_split(char const *s, char c);
char		**map_parser(char *file_name, int ***tab);
map_utils	*map_parsing(char *file_name, map_utils *fdf);
