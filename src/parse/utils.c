/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:26:13 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/15 13:29:09 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

char	*expand_env_var(const char *input)
{
	const char	*var;

	var = getenv(input + 1);
	if (!var)
		return (ft_strdup(""));
	return (ft_strdup(var));
}

int	ft_isspace(const char s)
{
	if (s == ' ' || s == '\t' || s == '\n' || s == '\v' || s == '\f'
		|| s == '\r')
		return (1);
	return (0);
}
