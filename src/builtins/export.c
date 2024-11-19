/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:42:17 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/19 08:50:02 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_export(void)
{
	extern char **environ;

	for (int i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
	return (0);
}

