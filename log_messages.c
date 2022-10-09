/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_messages.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arupert <arupert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:36:57 by arupert           #+#    #+#             */
/*   Updated: 2022/07/05 20:18:38 by arupert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	log_messages(t_rules *rules, int id, char *action)
{
	long int	timestamp;

	if (rules)
	{
		timestamp = (get_time() - rules->start_time) / 1000;
		pthread_mutex_lock(&rules->printing);
		pthread_mutex_lock(&rules->philos[id - 1].zombie_mutex);
		if (rules->philos[id - 1].zombie == 'n')
			printf("%lu %d %s\n", timestamp, id, action);
		pthread_mutex_unlock(&rules->philos[id - 1].zombie_mutex);
		pthread_mutex_unlock(&rules->printing);
	}
}

void	die_message(t_rules *rules, int id)
{
	long int	timestamp;

	timestamp = (get_time() - rules->start_time) / 1000;
	printf("%lu %d %s\n", timestamp, id, "died");
}

void	full_message(t_rules *rules)
{
	long int	timestamp;

	timestamp = (get_time() - rules->start_time) / 1000;
	printf("%lu %s\n", timestamp, "Everyone is full");
}
