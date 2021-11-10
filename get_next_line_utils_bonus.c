/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:05 by ashea             #+#    #+#             */
/*   Updated: 2020/05/29 15:35:13 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t		ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char		*ft_strchr(const char *str, int c)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == c)
		return ((char*)(str) + i);
	return (NULL);
}

char		*ft_strdup(const char *src)
{
	size_t	i;
	char	*src2;

	i = 0;
	while (src[i] != '\0')
		i++;
	src2 = (char*)malloc((i + 1) * sizeof(char));
	if (!src2)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		src2[i] = src[i];
		i++;
	}
	src2[i] = '\0';
	return (src2);
}

char		*ft_strljoin(char *s1, char *s2, size_t len)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	if ((join = (char*)malloc((len + 1) * sizeof(char))) == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && len--)
	{
		join[i] = s1[i];
		i++;
	}
	free(s1);
	s1 = NULL;
	j = 0;
	while (s2[j] && len--)
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}
