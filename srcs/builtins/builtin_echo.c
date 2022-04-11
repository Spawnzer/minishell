/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:00:31 by tshimoda          #+#    #+#             */
/*   Updated: 2022/04/11 13:30:16 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// function scanning the string *list and returns a bool depending on 
// if it only contains the valid option 'n' 
// for the builtin_echo handled in this project.
t_answer	ft_is_option(char valid, char *list)
{
	size_t	i;

	i = 0;
	while (list[i] != '\0')
	{
		printf("list[i] = %c\n", list[i]);
		if (valid == list[i])
			i++;
		else
			return (NO);
	}
	return (YES);
}

// bash behaviour : can receive multiple -n -n -n -nnnnnnnn options
// which remove the newline. If there is no -n as the first option, 
// it will treat the everything as text input.
// this function receive the array after the echo.
void	builtin_echo(char **options)
{
	t_answer	remove_nl;
	t_answer	is_option;

	if (*options == NULL)
		return ;
	remove_nl = NO;
	if (*options[0] == '-')
		remove_nl = ft_is_option('n', &(*options++)[1]);
	

	is_option = YES;
	while (*options != NULL && is_option == YES)
	{
		printf("current option = %s\n", *options);
		printf("is_option = %d\n", is_option);
		if (*options[0] == '-')
			is_option = ft_is_option('n', &(*options)[1]);
		options++;
	}
	while (*options != NULL)
	{
		printf("current option = %s\n", *options);
		write(1, *options, ft_strlen(*options));
		if (*(++options) != NULL)
			write(1, " ", 1);
	}
	
	printf("remove_nl = %d\n", remove_nl);
	if (remove_nl == NO)
		write(1, "\n", 1);
}
