/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lanch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arupert <arupert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:06:48 by arupert           #+#    #+#             */
/*   Updated: 2022/07/09 16:40:16 by arupert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	lock_right_first(t_philos *philo)
{
	pthread_mutex_lock(&(philo->right_fork));
	log_messages(philo->rules, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	log_messages(philo->rules, philo->id, "has taken a fork");
}

static void	unlock_right_first(t_philos *philo)
{
	pthread_mutex_unlock(&(philo->right_fork));
	pthread_mutex_unlock(philo->left_fork);
}

static void	think_eat_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->zombie_mutex);
	while (philo->zombie == 'n')
	{
		pthread_mutex_unlock(&philo->zombie_mutex);
		log_messages(philo->rules, philo->id, "is thinking");
		if (philo->id % 2 == 0)
			ft_usleep_zombie(200, philo);
		lock_right_first(philo);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->meal_mutex);
		log_messages(philo->rules, philo->id, "is eating");
		ft_usleep_zombie(philo->rules->time_to_eat, philo);
		unlock_right_first(philo);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->num_of_meals++;
		pthread_mutex_unlock(&philo->meal_mutex);
		log_messages(philo->rules, philo->id, "is sleeping");
		ft_usleep_zombie(philo->rules->time_to_sleep, philo);
		pthread_mutex_lock(&philo->zombie_mutex);
	}
	philo->killed_zombie = 'y';
	pthread_mutex_unlock(&philo->zombie_mutex);
}

static void	*philo_thread(void *ptr)
{
	t_philos	*philo;
	int			num_of_philos;

	philo = (t_philos *)ptr;
	pthread_mutex_lock(&philo->rules->nop_mutex);
	num_of_philos = philo->rules->num_of_philos;
	pthread_mutex_unlock(&philo->rules->nop_mutex);
	think_eat_sleep(philo);
	return (0);
}

void	start_the_lanch(t_rules *rules)
{
	pthread_t		id;
	int				i;

	i = 0;
	while (i < rules->num_of_philos)
	{
		pthread_create(&id, 0, philo_thread, &rules->philos[i]);
		pthread_detach(id);
		i++;
	}
}
