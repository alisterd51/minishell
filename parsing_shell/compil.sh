#!/usr/bin/env sh

######################################################################
# @author      : anclarma (anclarma@$HOSTNAME)
# @file        : compil
# @created     : Monday Jan 31, 2022 23:08:18 CET
#
# @description : 
######################################################################

cc -Wall -Wextra -Werror -fsanitize=address -fsanitize=leak -fsanitize=undefined -g3 *.c -lreadline
