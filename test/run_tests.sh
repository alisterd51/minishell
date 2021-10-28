#! /bin/sh

BOLD="\e[1m"
RESET="\e[0m"
LIGHT_RED="\e[91m"
LIGHT_GREEN="\e[92m"
LIGHT_CYAN="\e[96m"

test_default_main()
{
	make all
	printf "${LIGHT_CYAN}${BOLD}test_ast${RESET}\n"
	./test_ast
	printf "${LIGHT_CYAN}${BOLD}test_echo${RESET}\n"
	./test_echo
	printf "${LIGHT_CYAN}${BOLD}test_env${RESET}\n"
	./test_env
	printf "${LIGHT_CYAN}${BOLD}test_exit${RESET}\n"
	./test_exit
	printf "${LIGHT_CYAN}${BOLD}test_export${RESET}\n"
	./test_export
	printf "${LIGHT_CYAN}${BOLD}test_libft${RESET}\n"
	./test_libft
	printf "${LIGHT_CYAN}${BOLD}test_pwd${RESET}\n"
	./test_pwd
}

main()
{
	cd $(dirname $0)

	test_default_main
}

main "$@"
