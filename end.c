/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arupert <arupert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:33:34 by arupert           #+#    #+#             */
/*   Updated: 2022/07/09 17:37:39 by arupert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	wait_for_ending(t_rules *rules, int num_of_philos)
{
	int	i;
	int	num_of_killed;

	num_of_killed = 0;
	while (num_of_killed < num_of_philos)
	{
		i = 0;
		while (i < num_of_philos)
		{
			pthread_mutex_lock(&rules->philos[i].zombie_mutex);
			if (rules->philos[i].killed_zombie == 'y')
			{	
				rules->philos[i].killed_zombie = 'k';
				num_of_killed++;
			}
			pthread_mutex_unlock(&rules->philos[i].zombie_mutex);
			i++;
		}
	}
	return ;
}

static void	end_threads(t_rules *rules, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_lock(&rules->philos[i].zombie_mutex);
		rules->philos[i].zombie = 'y';
		pthread_mutex_unlock(&rules->philos[i].zombie_mutex);
		i++;
	}
	pthread_mutex_unlock(&rules->printing);
	if (num_of_philos != 1)
		wait_for_ending(rules, num_of_philos);
	return ;
}

void	kill_zombies(t_rules *rules, int id, int num_of_philos)
{
	pthread_mutex_lock(&rules->printing);
	die_message(rules, rules->philos[id - 1].id);
	end_threads(rules, num_of_philos);
}

int	everyone_is_full(t_rules *rules, int num_of_philos)
{
	pthread_mutex_lock(&rules->printing);
	full_message(rules);
	end_threads(rules, num_of_philos);
	return (1);
}

void	clean_program(t_rules *rules)
{
	pthread_mutex_destroy(&rules->nop_mutex);
	pthread_mutex_destroy(&rules->printing);
	pthread_mutex_destroy(&rules->program);
	free(rules->philos);
}
