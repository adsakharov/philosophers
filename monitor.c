/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arupert <arupert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 18:58:30 by arupert           #+#    #+#             */
/*   Updated: 2022/07/09 16:10:29 by arupert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	monitor_if_full(t_rules *rules, int num_of_philos)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < num_of_philos)
	{
		ft_usleep(500);
		pthread_mutex_lock(&rules->philos[i].meal_mutex);
		if (rules->philos[i].num_of_meals >= rules->num_must_eat)
		{
			pthread_mutex_unlock(&rules->philos[i].meal_mutex);
			full++;
		}
		else
		{
			pthread_mutex_unlock(&rules->philos[i].meal_mutex);
			return (0);
		}
		i++;
	}
	if (full == num_of_philos)
		return (everyone_is_full(rules, num_of_philos));
	return (0);
}

static int	monitor_if_dead(t_rules *rules, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		ft_usleep(500);
		pthread_mutex_lock(&rules->philos[i].meal_mutex);
		if (rules->philos[i].last_meal + rules->time_to_die < get_time())
		{
			pthread_mutex_unlock(&rules->philos[i].meal_mutex);
			kill_zombies(rules, i + 1, num_of_philos);
			return (1);
		}
		pthread_mutex_unlock(&rules->philos[i].meal_mutex);
		i++;
	}
	return (0);
}

void	*monitor6(void *ptr)
{
	t_rules	*rules;
	int		num_of_philos;

	rules = (t_rules *)ptr;
	pthread_mutex_lock(&rules->nop_mutex);
	num_of_philos = rules->num_of_philos;
	pthread_mutex_unlock(&rules->nop_mutex);
	while (1)
	{
		if (monitor_if_dead(rules, num_of_philos))
		{
			pthread_mutex_unlock(&rules->program);
			return (0);
		}
		if (monitor_if_full(rules, num_of_philos))
		{
			pthread_mutex_unlock(&rules->program);
			return (0);
		}
	}
}

void	*monitor5(void *ptr)
{
	t_rules	*rules;
	int		num_of_philos;

	rules = (t_rules *)ptr;
	pthread_mutex_lock(&rules->nop_mutex);
	num_of_philos = rules->num_of_philos;
	pthread_mutex_unlock(&rules->nop_mutex);
	while (1)
	{
		if (monitor_if_dead(rules, num_of_philos))
		{
			pthread_mutex_unlock(&rules->program);
			return (0);
		}
	}
	return (0);
}
