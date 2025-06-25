#!/bin/bash

#set -x
test_file="test_commands.txt"

while IFS= read -r command; do
    echo "Executing command: $command"
    echo "$command" | valgrind -q --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell
    #echo "$command" | ./minishell
done < "$test_file"
