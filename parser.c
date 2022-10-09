/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arupert <arupert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:07:10 by arupert           #+#    #+#             */
/*   Updated: 2022/07/05 20:22:13 by arupert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || \
			str[i] == '\t' || \
			str[i] == '\n' || \
			str[i] == '\r' || \
			str[i] == '\f' || \
			str[i] == '\v')
		i++;
	return (i);
}

static int	ft_atoi(const char *nptr)
{
	int			i;
	int			n;
	long int	x;

	i = check_space(nptr);
	n = 1;
	if (*(nptr + i) == '-' || *(nptr + i) == '+')
	{
		if (*(nptr + i) == '-')
			n = -1;
		i++;
	}
	x = 0;
	while (*(nptr + i) >= '0' && *(nptr + i) <= '9')
	{
		x = x * 10 + *(nptr + i) - 48;
		if (x > 2147483647 && n == 1)
			return (-1);
		if (x > 2147483648 && n == -1)
			return (0);
		i++;
	}
	x = x * n;
	return ((int)x);
}

unsigned long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, 0);
	return (current_time.tv_sec * 1000000 + current_time.tv_usec);
}

int	parse_args(int argc, char **argv, t_rules *rules)
{
	if (argc != 5 && argc != 6)
		return (error_message('a'));
	(*rules).num_of_philos = ft_atoi(argv[1]);
	(*rules).time_to_die = (long int)ft_atoi(argv[2]) * 1000;
	(*rules).time_to_eat = (long int)ft_atoi(argv[3]) * 1000;
	(*rules).time_to_sleep = (long int)ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		(*rules).num_must_eat = ft_atoi(argv[5]);
	(*rules).start_time = get_time();
	return (0);
}
