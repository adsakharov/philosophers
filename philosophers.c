/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arupert <arupert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:46:11 by arupert           #+#    #+#             */
/*   Updated: 2022/07/05 20:22:00 by arupert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_rules			rules;
	pthread_t		id;
	pthread_t		id2;

	if (parse_args(argc, argv, &rules))
		return (-1);
	if (check_errors(&rules, argc))
		return (-1);
	pthread_create(&id, 0, init, &rules);
	pthread_join(id, 0);
	if (rules.error != 0)
		return (error_message('m'));
	start_the_lanch(&rules);
	if (argc == 6)
		pthread_create(&id2, 0, monitor6, &rules);
	else
		pthread_create(&id2, 0, monitor5, &rules);
	pthread_detach(id2);
	pthread_mutex_lock(&rules.program);
	clean_program(&rules);
	return (0);
}
