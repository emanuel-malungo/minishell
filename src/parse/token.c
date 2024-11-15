/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:24:11 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/15 15:21:35 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	ft_count_word(char const *s)
{
	int	i;
	int	word_count;
	int	in_quotes;

	i = 0;
	word_count = 0;
	in_quotes = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			in_quotes = !in_quotes;
			i++;
			continue ;
		}
		if (!in_quotes && !isspace(s[i]) && s[i] != '|' && s[i] != '>'
			&& s[i] != '<')
		{
			word_count++;
			while (s[i] && (!isspace(s[i]) && s[i] != '|' && s[i] != '>'
					&& s[i] != '<'))
				i++;
		}
		else if (!in_quotes && (s[i] == '|' || s[i] == '>' || s[i] == '<'))
		{
			word_count++;
			i++;
		}
		else
			i++;
	}
	return (word_count);
}

int	ft_wordsize(char const *str, int i)
{
	int	size;

	size = 0;
	while (str[i] && !isspace(str[i]) && str[i] != '|' && str[i] != '>'
		&& str[i] != '<')
	{
		size++;
		i++;
	}
	return (size);
}
void	ft_free(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

char	**ft_token(char const *s)
{
	int		i;
	int		j;
	int		size;
	char	**strs;
	char	quote;
	int		var_size;

	i = 0;
	j = 0;
	size = 0;
	strs = (char **)malloc((ft_count_word(s) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (s[i])
	{
		while (s[i] && isspace(s[i]))
			i++;
		if (s[i] == '\"' || s[i] == '\'')
		{
			quote = s[i++];
			size = 0;
			while (s[i] && s[i] != quote)
			{
				size++;
				i++;
			}
			strs[j] = (char *)malloc(size + 1);
			if (!strs[j])
			{
				ft_free(strs, j);
				return (NULL);
			}
			strncpy(strs[j], &s[i - size], size);
			strs[j++][size] = '\0';
			i++;
		}
		else if (s[i] == '$')
		{
			var_size = 0;
			i++;
			while (s[i] && (isalnum(s[i]) || s[i] == '_'))
			{
				var_size++;
				i++;
			}
			strs[j] = (char *)malloc(var_size + 1);
			if (!strs[j])
			{
				ft_free(strs, j);
				return (NULL);
			}
			strncpy(strs[j], &s[i - var_size], var_size);
			strs[j++][var_size] = '\0';
		}
		else if (!isspace(s[i]) && s[i] != '|' && s[i] != '>' && s[i] != '<')
		{
			size = ft_wordsize(s, i);
			strs[j] = (char *)malloc(size + 1);
			if (!strs[j])
			{
				ft_free(strs, j);
				return (NULL);
			}
			strncpy(strs[j], &s[i], size);
			strs[j++][size] = '\0';
			i += size;
		}
		else if (s[i] == '>' && s[i + 1] == '>')
		{
			strs[j] = (char *)malloc(3);
			if (!strs[j])
			{
				ft_free(strs, j);
				return (NULL);
			}
			strs[j][0] = s[i];
			strs[j][1] = s[i + 1];
			strs[j++][2] = '\0';
			i += 2;
		}
		else if (s[i] == '<' && s[i + 1] == '<')
		{
			strs[j] = (char *)malloc(3);
			if (!strs[j])
			{
				ft_free(strs, j);
				return (NULL);
			}
			strs[j][0] = s[i];
			strs[j][1] = s[i + 1];
			strs[j++][2] = '\0';
			i += 2;
		}
		else if (s[i] == '|' || s[i] == '>' || s[i] == '<')
		{
			strs[j] = (char *)malloc(2);
			if (!strs[j])
			{
				ft_free(strs, j);
				return (NULL);
			}
			strs[j][0] = s[i];
			strs[j++][1] = '\0';
			i++;
		}
		else
		{
			i++;
		}
	}
	strs[j] = NULL;
	return (strs);
}
