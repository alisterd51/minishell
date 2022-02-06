/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 00:46:40 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/06 02:09:26 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"

static int	ft_perror(char const *str)
{
	perror(str);
	return (-1);
}

static int	read_heredoc(int fd, char const *terminat, int expend)
{
	char	*line;

	(void)expend;
	line = readline(DEFAULT_PS2);
	while (line && ft_strcmp(terminat, line))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(DEFAULT_PS2);
	}
	free(line);
	return (0);
}

int	fd_heredoc(char *file, int expend, t_list **lst_env)
{
	int		fd;
	char	*heredoc;
	pid_t	pid_heredoc;
	int		status;

	heredoc = new_heredoc();
	if (heredoc == NULL)
		return (ft_perror("new heredoc"));
	fd = open(heredoc, O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (ft_perror(heredoc));
	signal(SIGINT, SIG_IGN);
	pid_heredoc = fork();
	if (pid_heredoc == 0)
	{
		signal(SIGINT, handler_int_heredoc);
		read_heredoc(fd, file, expend);
		close(fd);
		clean_env(lst_env);
		clean_colector();
		clean_heredoc(2);
		exit(ft_get_status());
	}
	else
		waitpid(pid_heredoc, &status, 0);
	ft_set_status(WEXITSTATUS(status));
	signal(SIGINT, handler_int);
	close(fd);
	fd = open(heredoc, O_RDONLY);
	if (fd == -1)
		return (ft_perror(heredoc));
	to_fd_colector(fd);
	return (fd);
}
