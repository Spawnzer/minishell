/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubeau <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:42:54 by adubeau           #+#    #+#             */
/*   Updated: 2022/04/30 16:34:26 by adubeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <string.h>

int		get_fdI(t_node *current, int i, int j)
{

	int fd;
	char *file;

	fd = 0;
	while (current->value[i])
	{
		if (current->value[i] == ('<'))
			if (current->value[i + 1] != '<')
			{
				while (!(ft_isalnum(current->value[i])))
					i++;
				while (ft_isalnum(current->value[i++]))
					j++;
				file = ft_substr(current->value, i-j, j);
				fd = open(file, O_RDONLY);
			}
		i++;
	}
	return (fd);
}
int	get_fdO(t_node *current, char *value, int i, int j, int fd)
{
	int k;
	char *file;
	char *tmp;
	char type;
	printf("HI\n");
	while (value[i])
	{
		printf("fdo current->value:%s, i=%d, char =%c\n", value, i, value[i]);
		j = 0;
		if (value[i] == '>')
		{
			k = i - 1;
			if (value[i + 1] == '>') {
				current->type = 'a';
				i++;
			}
			else
				type = 'c';
			printf("value =%s, i =%d, j =%c\n",value, i, j);
			while (value[i] == ' ' || value[i] == '>')
				i++;
			while (value[i] && value[i] != ' ' && value[i] != '>')
			{
				j++;
				i++;
			}
			file = ft_substr(value, i - j, j);
			printf("value-f =%s, i =%d, j =%d\n",value, i, j);

			if (ft_is_present('/', file))
			{
				value = "";
				printf("%s: No such file or directory\n", file);
				return (1);
			}
			printf("file:%s\n", file);
			printf("k =%d, i =%d, j =%d\n",k, i, j);

			tmp = ft_strjoin(ft_substr(value, 0, k + 1), (value + i));
			printf("tmp:%s\n", tmp);
			free(value);
			value = tmp;
			printf("current->value:%s\n", value);
			tmp = NULL;
			//if (type == 'c')
				fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
				file=NULL;
			//else
			//	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
			/*if (ft_is_present('>', value))
				return (get_fdO(value, 0, 0, fd));
			else
				return (fd);*/
			i = -1;
		}
		i++;
	}
	printf("current->value return:%s\n", value);
	current->value = value;
	return (fd);
}
