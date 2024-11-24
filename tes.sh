#!/bin/bash

# Função para testar um comando no minishell
test_command() {
    echo "Testando comando: $1"
    echo "$1" | ./minishell
    echo "-----------------------------------------------------"
}

# Limpeza (opcional)
clear

# Exemplo de comandos para testar
echo "Iniciando testes no minishell..."

# Comandos básicos

# Comando simples de echo
test_command "echo Hello, World!"

# Comando simples com variáveis de ambiente
export MY_VAR="Testando variáveis"
test_command "echo \$MY_VAR"

# Comando com aspas simples
test_command "echo 'Texto com aspas simples'"

# Comando com aspas duplas
test_command "echo \"Texto com aspas duplas\""

# Comando com múltiplos argumentos
test_command "echo This is a test"

# Comando com espaço extra entre os argumentos
test_command "   echo    Extra   spaces  "

# Comando com redirecionamento para um arquivo
test_command "echo Hello > output.txt"
test_command "cat output.txt"

# Comando com redirecionamento de erro
test_command "echo Error message 1>&2"

# Comando com redirecionamento de erro para um arquivo
test_command "echo Error message 1>error.txt"
test_command "cat error.txt"

# Comando de leitura de arquivo
test_command "cat < output.txt"

# Comando com múltiplos redirecionamentos
test_command "echo Hello > output1.txt 2> output2.txt"
test_command "cat output1.txt"
test_command "cat output2.txt"

# Testando pipes
test_command "echo Hello | grep Hello"

# Testando comando com pipe e redirecionamento
test_command "echo Hello | grep Hello > pipe_output.txt"
test_command "cat pipe_output.txt"

# Testando comandos com operadores lógicos (&&)
test_command "echo Hello && echo World"

# Testando comandos com operadores lógicos (||)
test_command "false_command || echo Comando falhou, mas echo funciona"

# Testando comando com variáveis dentro de comandos
export PATH="/usr/bin:/bin"
test_command "echo \$PATH"

# Testando comandos com variáveis de ambiente
test_command "echo \$SHELL"
test_command "echo \$HOME"

# Testando comandos com subshell (parênteses)
test_command "(echo Inside Subshell)"

# Testando a execução de múltiplos comandos (sequência de comandos)
test_command "echo First command; echo Second command; echo Third command"

# Testando redirecionamento de múltiplos arquivos
test_command "echo Hello > output1.txt 2> output2.txt; cat output1.txt; cat output2.txt"

# Comando com um operador de redirecionamento desconhecido
test_command "echo Hello > output.txt |"

# Comando com variáveis de shell
test_command "echo \$USER"

# Testando comandos com aspas e redirecionamento
test_command "echo \"Texto com aspas e > redirecionamento\" > output_with_quotes.txt"
test_command "cat output_with_quotes.txt"

# Testando comando com operador lógico misturado com pipes
test_command "echo Hello && echo World | grep World"

# Comando inválido
test_command "invalid_command"

# Testando um comando complexo com redirecionamento, variáveis, e pipes
test_command "echo \$USER > user.txt; cat user.txt | grep '\$USER'"

# Testando comandos com Heredoc (<<)
test_command "cat <<EOF
Hello, this is a heredoc test.
EOF"

# Testando comando de execução de fundo (background process)
test_command "sleep 1 &"

echo "Testes concluídos!"
