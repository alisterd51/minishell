#! /bin/dash

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
	printf "${LIGHT_CYAN}${BOLD}test_cd ..${RESET}\n"
	./test_cd ".."
	printf "${LIGHT_CYAN}${BOLD}test_solve_path cat${RESET}\n"
	./test_solve_path "cat"
}

test_minishell()
{
	cd ..
	make fclean debug
	printf "${LIGHT_CYAN}${BOLD}minishell < cmd1${RESET}\n"
	./minishell < ./test/cmd1
	printf "${LIGHT_CYAN}${BOLD}minishell < cmd2${RESET}\n"
	./minishell < ./test/cmd2
	printf "${LIGHT_CYAN}${BOLD}minishell < cmd3${RESET}\n"
	./minishell < ./test/cmd3
	printf "${LIGHT_CYAN}${BOLD}minishell < cmd4${RESET}\n"
	./minishell < ./test/cmd4
}

main()
{
	cd $(dirname $0)

	test_default_main
	test_minishell
	make fclean
}

main "$@"
