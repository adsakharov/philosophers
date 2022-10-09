/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arupert <arupert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:53:08 by arupert           #+#    #+#             */
/*   Updated: 2022/07/09 17:23:41 by arupert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosophers(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->num_of_philos)
	{
		pthread_mutex_init(&rules->philos[i].right_fork, 0);
		pthread_mutex_init(&rules->philos[i].meal_mutex, 0);
		pthread_mutex_init(&rules->philos[i].zombie_mutex, 0);
		if (i != 0)
			rules->philos[i].left_fork = &rules->philos[i - 1].right_fork;
		rules->philos[i].last_meal = rules->start_time;
		rules->philos[i].num_of_meals = 0;
		rules->philos[i].id = i + 1;
		rules->philos[i].rules = rules;
		rules->philos[i].zombie = 'n';
		rules->philos[i].killed_zombie = 'n';
		i++;
	}
	rules->philos[0].left_fork = \
	&rules->philos[rules->num_of_philos - 1].right_fork;
}

void	*init(void *ptr)
{
	t_rules	*rules;

	rules = (t_rules *)ptr;
	rules->error = 0;
	pthread_mutex_init(&rules->nop_mutex, 0);
	pthread_mutex_init(&rules->printing, 0);
	pthread_mutex_init(&rules->program, 0);
	pthread_mutex_lock(&rules->program);
	rules->philos = malloc (sizeof(t_philos) * rules->num_of_philos);
	if (!rules->philos)
	{
		rules->error = -1;
		return (0);
	}
	init_philosophers(rules);
	return (0);
}
