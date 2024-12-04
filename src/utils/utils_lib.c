/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 08:06:23 by emalungo          #+#    #+#             */
/*   Updated: 2024/12/03 08:43:18 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_delim(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*saveptr;
	char		*token_start;

	if (!str && !saveptr)
		return (NULL);
	if (!str)
		str = saveptr;
	while (*str && is_delim(*str, delim))
		str++;
	if (*str == '\0')
	{
		saveptr = NULL;
		return (NULL);
	}
	token_start = str;
	while (*str && !is_delim(*str, delim))
		str++;
	if (*str)
	{
		*str = '\0';
		str++;
	}
	saveptr = str;
	return (token_start);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*str;
	size_t	i;
	size_t	len;

	i = -1;
	len = ft_strlen(s);
	if (n > len)
		n = len;
	str = (char *)malloc(n + 1);
	if (str == NULL)
		return (NULL);
	while (++i < n)
		str[i] = s[i];
	str[n] = '\0';
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}