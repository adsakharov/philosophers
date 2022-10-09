/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arupert <arupert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:10:42 by arupert           #+#    #+#             */
/*   Updated: 2022/07/09 16:45:40 by arupert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(unsigned long usec)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, 0);
	gettimeofday(&now, 0);
	while (((unsigned long)(now.tv_sec - start.tv_sec)) * 1000000 + \
	(unsigned long)(now.tv_usec - start.tv_usec) < usec)
	{
		usleep(10);
		gettimeofday(&now, 0);
	}
	return ;
}

void	ft_usleep_zombie(unsigned long usec, t_philos *philo)
{
	pthread_mutex_lock(&philo->zombie_mutex);
	if (philo->zombie == 'n')
	{
		pthread_mutex_unlock(&philo->zombie_mutex);
		ft_usleep(usec);
	}
	else
		pthread_mutex_unlock(&philo->zombie_mutex);
	return ;
}
