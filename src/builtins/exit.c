/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:26:53 by emalungo          #+#    #+#             */
/*   Updated: 2025/01/11 20:43:46 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_within_int_limits(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (sign >= 1 && result > LONG_MAX)
			return (0);
		if (sign == -1 && (-result) < LONG_MIN)
			return (0);
		str++;
	}
	if (*str != '\0')
		return (0);
	return (1);
}

void	check_exit_args(t_node *current, int *arg_count, int *exit_code, t_shell *shell)
{
	t_node	*temp;

	temp = current->next;
	*arg_count = 0;
	while (temp)
	{
		if (ft_strcmp(temp->type, "argument") == 0)
		{
			(*arg_count)++;
			if (!is_within_int_limits(temp->value))
			{
				printf("exit\n");
				shell->exit_status = 1;
				printf("minishell: exit: %s: numeric argument required\n",
					temp->value);
				exit(EXIT_FAILURE);
			}
			*exit_code = ft_atoi(temp->value);
		}
		temp = temp->next;
	}
}

void	ft_exit(t_node **current, t_shell *shell)
{
	int	arg_count;
	int	exit_code;

	arg_count = 0;
	exit_code = 0;
	if (!current || !(*current))
	{
		printf("exit\n");
		shell->exit_status = 1;
		exit(0);
	}
	check_exit_args(*current, &arg_count, &exit_code, shell);
	if (arg_count > 1)
	{
		printf("exit\n");
		shell->exit_status = 1;
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	printf("exit\n");
	exit(exit_code);
}
