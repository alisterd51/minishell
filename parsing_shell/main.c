/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:22:58 by lzaccome          #+#    #+#             */
/*   Updated: 2022/01/31 23:10:59 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "test.h"

int	ft_strclen(char *str, char c, int i)
{
	int	j;

	j = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		j++;
	}
	return (j);
}

int	ft_strarglen(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|'
		&& str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
	{
		i++;
		j++;
	}
	return (j);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

char	*ft_strndup(char *str, int size, int i)
{
	char	*word;
	int		j;

	j = 0;
	word = malloc(sizeof(char) * size + 1);
	if (!word)
		return (NULL);
	while (str[i] && j < size)
	{
		word[j] = str[i];
		i++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

t_cmd	*parsing_shell(char *str, char **envp)
{
	t_cmd	*cmd;

	(void)envp;
	cmd = get_cmd(str, envp);
	return (cmd);
}
/*
int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	(void)ac;
	cmd = NULL;
	if (ac <= 1)
		return (0);
	cmd = parsing_shell(av[1], envp);
	printf("av : %s\n", av[1]);
	tmp = cmd;
	while (cmd)
	{
		printf("token : %s, %d, %d\n", cmd->word, cmd->type, cmd->space);
		cmd = cmd->next;
	}
	free_lst(&tmp);
	return (0);
}
*/
int	main(int ac, char **av, char **env)
{
	char	*line;
	t_cmd	*cmd;
	t_cmd	*tmp;

	line = readline("\033[1;34mtest-parsing \033[1;32mv0.1\033[0m$ ");
	while (line)
	{
		add_history(line);
		cmd = parsing_shell(line, env);
		printf("av : %s\n", line);
		tmp = cmd;
		while (cmd)
		{
			printf("token : %s, %d, %d\n", cmd->word, cmd->type, cmd->space);
			cmd = cmd->next;
		}
		free_lst(&tmp);
		free(line);
		line = readline("\033[1;34mtest-parsing \033[1;32mv0.1\033[0m$ ");
	}
	(void)ac;
	(void)av;
	return (0);
}
