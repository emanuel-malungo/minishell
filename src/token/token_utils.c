/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:35:27 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/24 14:50:15 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_is(char c, int j) {
    if (j == 0)
        return (c == '|' || c == '>' || c == '<');
    else if (j == 1)
        return (c == '\"' || c == '\'');
    else if (j == 2)
        return (c == ' ');
    else if (j == 3)
        return (c != ' ' && c != '|' && c != '>' && c != '<' && c);
    return 0;
}

int	wordsize(const char *str, int i)
{
	int size;

	size = 0;
	while (str[i] && !check_is(str[i], 2) && !check_is(str[i], 0))
	{
		size++;
		i++;
	}
	return (size);
}

static void	process_token(const char *input, int *i, int *count)
{
	char	quote;

	if (input[*i] == '\'' || input[*i] == '\"')
	{
		quote = input[(*i)++];
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (input[*i])
			(*i)++;
		(*count)++;
	}
	else if (input[*i] == '$')
	{
		(*i)++;
		while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
			(*i)++;
		(*count)++;
	}
	else if (check_is(input[*i], 3))
	{
		while (input[*i] && check_is(input[*i], 3))
			(*i)++;
		(*count)++;
	}
}

int	count_word(const char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		if (check_is(input[i], 0))
		{
			while (input[i] && check_is(input[i], 0))
				i++;
			count++;
		}
		else
			process_token(input, &i, &count);
	}
	return (count);
}