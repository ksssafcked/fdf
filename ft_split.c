/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:08:49 by lsaiti            #+#    #+#             */
/*   Updated: 2024/11/21 18:42:15 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

void	*ft_freesplit(char **split, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
		free(split[i++]);
	free(split);
	return (NULL);
}

int	count_words(const char *str, char charset)
{
	int	word;

	word = 0;
	while (*str)
	{
		while (*str == charset && *str != '\0')
			str++;
		if (*str != '\0')
		{
			word++;
			str++;
		}
		while (*str != '\0' && *str != charset)
			str++;
	}
	return (word);
}

char	*ft_word(const char *src, char charset)
{
	int		i;
	int		size;
	char	*dest;

	size = 0;
	while (src[size] && charset != src[size])
	{
		size++;
	}
	dest = malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*ft_splitchar(char **split, char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (c == s[i] && s[i])
			i++;
		if (s[i])
		{
			split[j] = ft_word(&s[i], c);
			if (!split[j])
				return (ft_freesplit(split, j));
			j++;
		}
		while (c != s[i] && s[i])
			i++;
	}
	split[j] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!split)
		return (NULL);
	if (!ft_splitchar(split, s, c))
		return (NULL);
	return (split);
}
