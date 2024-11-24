/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:36:39 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/22 15:16:21 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Função para converter a lista de variáveis de ambiente (env_list) em um vetor de strings
char **convert_env_list_to_array(t_env_node *env_list)
{
    int count = 0;
    t_env_node *tmp = env_list;

    // Contar quantas variáveis de ambiente há
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }

    // Alocar memória para o vetor de strings
    char **envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
    {
        perror("malloc");
        return NULL;
    }

    // Preencher o vetor com as variáveis de ambiente
    int i = 0;
    tmp = env_list;
    while (tmp)
    {
        envp[i] = malloc(strlen(tmp->name) + strlen(tmp->value) + 2); // +1 para '=' e +1 para '\0'
        if (!envp[i])
        {
            perror("malloc");
            return NULL;
        }
        sprintf(envp[i], "%s=%s", tmp->name, tmp->value);
        tmp = tmp->next;
        i++;
    }

    envp[i] = NULL;  // O último elemento deve ser NULL
    return envp;
}

// Função para executar comandos externos
void execute_external_command(t_node *command_node, t_env_node *env_list)
{
    char *path_env = getenv("PATH");
    if (!path_env)
    {
        printf("Error: PATH variable not found\n");
        return;
    }

    char **directories = ft_split(path_env, ':');
    if (!directories)
    {
        perror("Error splitting PATH");
        return;
    }

    char *command = command_node->value;
    char *command_path = NULL;

    for (int i = 0; directories[i]; i++)
    {
        command_path = malloc(strlen(directories[i]) + strlen(command) + 2);
        if (!command_path)
        {
            perror("malloc");
            return;
        }
        sprintf(command_path, "%s/%s", directories[i], command);
        if (access(command_path, X_OK) == 0)
            break;
        free(command_path);
        command_path = NULL;
    }
    if (command_path)
    {
        int arg_count = 0;
        t_node *arg_node = command_node->next;
        while (arg_node)
        {
            arg_count++;
            arg_node = arg_node->next;
        }
        char **argv = malloc(sizeof(char *) * (arg_count + 2));
        if (!argv)
        {
            perror("malloc");
            free(command_path);
            return;
        }
        argv[0] = command;
        arg_node = command_node->next;
        int i = 1;
        while (arg_node)
        {
            argv[i++] = arg_node->value;
            arg_node = arg_node->next;
        }
        argv[i] = NULL;
        char **envp = convert_env_list_to_array(env_list);
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            free(command_path);
            free(envp);
            free(argv);
            return;
        }
        if (pid == 0)
        {
            if (execve(command_path, argv, envp) == -1)
            {
                perror("execve");
                free(command_path);
                free(envp);
                free(argv);
                exit(1);
            }
        }
        else
            waitpid(pid, NULL, 0);
        free(command_path);
        free(envp);
        free(argv);
    }
    else
        printf("%s: Command not found\n", command);
    for (int i = 0; directories[i]; i++)
        free(directories[i]);
    free(directories);
}