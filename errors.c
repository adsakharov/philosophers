/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arupert <arupert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:13:54 by arupert           #+#    #+#             */
/*   Updated: 2022/07/08 14:18:23 by arupert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_errors(t_rules *rules, int argc)
{
	if ((*rules).num_of_philos < 1)
		return (error_message('b'));
	if ((*rules).time_to_die < 1)
		return (error_message('b'));
	if ((*rules).time_to_eat < 1)
		return (error_message('b'));
	if ((*rules).time_to_sleep < 1)
		return (error_message('b'));
	if (argc == 6)
	{
		if ((*rules).num_must_eat < 0)
			return (error_message('b'));
	}
	else
		(*rules).num_must_eat = -1;
	return (0);
}

int	error_message(char error_type)
{
	if (error_type == '1')
		printf("Error\nWrong number of arguments\n");
	else if (error_type == 'a')
		printf("Error\nWrong arguments\n");
	else if (error_type == 'm')
		printf("Error\nMemmory was not allocated\n");
	else if (error_type == 'b')
		printf("Error\nArguments should be natural numbers\n");
	return (-1);
}
