#!/usr/bin/env sh

valgrind --leak-check=full --show-leak-kinds=all --suppressions=minimal.supp ./minishell
