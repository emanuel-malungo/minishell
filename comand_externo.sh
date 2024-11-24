#!/bin/bash

# Função para testar um comando no minishell
test_command() {
    echo "Testando comando: $1"
    echo "$1" | ./minishell
    echo "-----------------------------------------------------"
}

# Limpeza de arquivos temporários
cleanup() {
    rm -f output.txt error.txt output1.txt output2.txt pipe_output.txt output_with_quotes.txt user.txt
}

# Limpeza inicial
clear
cleanup

# Exemplo de comandos para testar
echo "Iniciando testes no minishell..."

# Comandos básicos
test_command "echo Hello, World!"    # Comando interno
test_command "pwd"                   # Comando interno
test_command "ls"                    # Comando externo
test_command "cat example.txt"       # Comando externo (exemplo de arquivo, você pode criar este arquivo para testar)

# Comando com variáveis de ambiente (interno)
export MY_VAR="Testando variáveis"
test_command "echo \$MY_VAR"

# Comando com aspas simples (interno)
test_command "echo 'Texto com aspas simples'"

# Comando com aspas duplas (interno)
test_command "echo \"Texto com aspas duplas\""

# Comando com múltiplos argumentos (interno)
test_command "echo This is a test"

# Comando com espaço extra entre os argumentos (interno)
test_command "   echo    Extra   spaces  "

# Testando comando de leitura de arquivo (externo)
test_command "cat example.txt"    # Certifique-se de ter um arquivo `example.txt` criado

# Testando comandos com variáveis de ambiente (interno)
test_command "echo \$SHELL"
test_command "echo \$HOME"

# Testando execução de múltiplos comandos (sequência de comandos internos)
test_command "echo First command; echo Second command; echo Third command"

# Testando comandos externos
test_command "ls"      # Comando externo para listar arquivos
test_command "pwd"     # Comando externo para mostrar diretório atual
test_command "cat"     # Comando externo para ler arquivo

# Limpeza final
cleanup

echo "Testes concluídos!"
