/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:18:12 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/11 15:30:55 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_quotes(char *str)
{
	int		len;
	int		j;
	int		i;
	char	*cleaned;

	i = -1;
	len = ft_strlen(str);
	cleaned = malloc(sizeof(char) * (len + 1));
	if (!cleaned)
		return (NULL);
	j = 0;
	while (++i < len)
	{
		if (str[i] != '\'' && str[i] != '"')
			cleaned[j++] = str[i];
	}
	cleaned[j] = '\0';
	return (cleaned);
}
