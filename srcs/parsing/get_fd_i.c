/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:15:52 by tshimoda          #+#    #+#             */
/*   Updated: 2022/05/31 15:47:01 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_main(t_node *current, char *file)
{
	current->type = 'h';
	current->eof = ft_strdup(file);
	current->fd_i = dup(STDIN_FILENO);
	heredoc_preparation(current);
	free(file);
	file = NULL;
}

int	try_open_file(t_node *current, char *file, int fd)
{
	if (fd != STDIN_FILENO)
		close(fd);
	fd = open(file, O_RDONLY);
	if (fd == FAIL)
	{
		current->type = 'e';
		free(current->value);
		current->value = ft_strdup(" ");
		printf("minishell: %s: No such file or directory\n", file);
		get_minishell()->exit_nb = ERROR_1;
	}
	free(file);
	file = NULL;
	return (fd);
}

void	get_fd_i_value(t_node *cu, int *i, int *j, int k)
{
	char	*sub_str;
	char	*join_str;
	//static int b = 0;

	sub_str = ft_substr(cu->value, 0, k);
	join_str = ft_strjoin(sub_str, (cu->value + *i));
	free(sub_str);
	free(cu->value);
	cu->value = join_str;
	*i = -1;
	*j = 0;
	cu->value = ft_trim(cu->value, ' ');
	if (ft_strlen(cu->value) == 0)
		cu->type = 'e';
	//printf("b = %d, value = '%s', len = %d, type = %c\n",b++, cu->value, ft_strlen(cu->value), cu->type);
}

void	get_fd_left_redirection(t_node *current, int *i, int *j)
{
	while (current->value[*i] == ' ' || current->value[*i] == '<')
		*i += 1;
	while (current->value[*i] && current->value[*i] != ' ' \
	&& current->value[*i] != '<')
		dual_increments(i, j);
}

int	get_fd_i(t_node *current, int i, int j, int fd)
{
	char	*file;
	int		k;

	while (current->value[i])
	{
		if (current->value[i] == '\'' || current->value[i] == '"')
			ft_iterate(current, &i, current->value[i]);
		if (current->value[i] == '<')
		{
			k = i;
			get_fd_left_redirection(current, &i, &j);
			file = ft_substr(current->value, i - j, j);
			if (current->value[k] == '<' && current->value[k + 1] == '<')
				heredoc_main(current, file);
			else
				fd = try_open_file(current, file, fd);
			if (fd == FAIL)
				break ;
			get_fd_i_value(current, &i, &j, k);
		}
		i++;
	}
	if (current->type != 'h')
		return (fd);
	else
		return (current->fd_i);
}
