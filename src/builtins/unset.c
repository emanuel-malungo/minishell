/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:24:10 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/19 08:31:54 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void ft_unset(t_env **env_list, const char *name)
{
    t_env *current;
    t_env *prev;

    if (name == NULL)
        perror("unset");
    prev = NULL;
    current = *env_list;
    while (current)
    {
        if (strcmp(current->name, name) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *env_list = current->next;
            free(current->name);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    perror("unset");
}