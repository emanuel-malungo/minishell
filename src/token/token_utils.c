/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:35:27 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/18 12:23:09 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_is(char c, int j)
{
	if (j == 0)
		return (c == '|' || c == '>' || c == '<' || c == '&' || c == ';');
	else if (j == 1)
		return (c == '\"' || c == '\'');
	else if (j == 2)
		return (c == ' ');
	else if (j == 3)
		return (c == '|' || c == '>' || c == '<' || c == '&' || c == ';');
	else if (j == 4)
	{
		return (c != ' ' && c != '|' && c != '>' && c != '<' && c != '$'
			&& c != '&' && c != ';' && c != '\'' && c != '\"');
	}
	return (0);
}

int	count_word(char const *str)
{
	int		i;
	int		c;
	int		check_quotes;
	char	quote_type;

	i = 0;
	c = 0;
	check_quotes = 0;
	quote_type = 0;
	while (str[i])
	{
		if (check_is(str[i], 1) && (!check_quotes || str[i] == quote_type))
		{
			if (!check_quotes)
				quote_type = str[i];
			check_quotes = !check_quotes;
			i++;
			continue ;
		}
		if (!check_quotes && !check_is(str[i], 2) && !check_is(str[i], 0))
		{
			c++;
			while (str[i] && !check_is(str[i], 2) && !check_is(str[i], 0))
			{
				if (check_is(str[i], 1))
					break ;
				i++;
			}
		}
		else if (!check_quotes && check_is(str[i], 0))
		{
			c++;
			if ((str[i] == '>' || str[i] == '<' || str[i] == '&') && str[i
				+ 1] == str[i])
				i++;
			i++;
		}
		else
			i++;
	}
	if (check_quotes)
		return (-1);
	return (c);
}

int	wordsize(char const *str, int i)
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