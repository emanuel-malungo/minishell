/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:38:54 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/29 13:06:41 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	size_t len1, len2;
	if (!s1 || !s2)
		return (NULL);
	len1 = strlen(s1);
	len2 = strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	strcpy(joined, s1);
	strcat(joined, s2);
	free(s1); 
	return (joined);
}

char	*get_env_value(const char *var, t_env_node *env_list)
{
	t_env_node	*current;

	current = env_list;
	while (current)
	{
		if (strcmp(current->name, var) == 0)
			return (current->value);
		current = current->next;
	}
	return ("");
}

char *expand_input(char *input, t_env_node *env_list)
{
    char *result = ft_strdup("");
    int i = 0;
	
    while (input[i])
	{
        if (input[i] == '\'')
			return (input);
		else
		{
			if (input[i] == '$' && input[i + 1] && input[i + 1] != ' ') {
            i++; 
            int start = i;


            while (ft_isalnum(input[i]) || input[i] == '_') i++;
            char *var_name = ft_substr(input, start, i - start);
            char *value = get_env_value(var_name, env_list);
            if (!value)
                value = ft_strdup("");

            char *temp = ft_strjoin(result, value);
            result = temp;

			} else {
				int start = i;
				while (input[i] && input[i] != '$') i++;

				char *literal = ft_substr(input, start, i - start);
				char *temp = ft_strjoin(result, literal);
				result = temp;
			}
		}
    }
    return (result);
}


int	main(void)
{
	t_bash	*bash;
	char	*expanded_input;

	bash = init_bash();
	while (1)
	{
		bash->input = readline("minishell$> ");
		if (!bash->input)
			break ;
		add_history(bash->input);
		expanded_input = expand_input(bash->input, bash->env_list);
		bash->tokens = tokenizer(expanded_input, bash->env_list);
		bash->syntax_list = parse_tokens(bash->tokens);
		print_list(bash->syntax_list);
		builtins(bash->syntax_list, bash->env_list);
		free(bash->input);
	}
	return (0);
}
