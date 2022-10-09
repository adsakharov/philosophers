/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arupert <arupert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:46:35 by arupert           #+#    #+#             */
/*   Updated: 2022/07/09 17:23:47 by arupert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

struct	s_philos;

typedef struct s_rules
{
	int				num_of_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				num_must_eat;
	unsigned long	start_time;
	struct s_philos	*philos;
	int				error;
	pthread_mutex_t	printing;
	pthread_mutex_t	program;
	pthread_mutex_t	nop_mutex;
}				t_rules;

typedef struct s_philos
{
	int					id;
	unsigned long		last_meal;
	int					num_of_meals;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		meal_mutex;
	char				zombie;
	char				killed_zombie;
	pthread_mutex_t		zombie_mutex;
	t_rules				*rules;
}				t_philos;

//end.c
void			kill_zombies(t_rules *rules, int id, int num_of_philos);
int				everyone_is_full(t_rules *rules, int num_of_philos);
void			clean_program(t_rules *rules);

//errors.c
int				check_errors(t_rules *rules, int argc);
int				error_message(char error_type);

//init.c
void			*init(void *ptr);

//lanch.c
void			start_the_lanch(t_rules *rules);

//log_message.c
void			log_messages(t_rules *rules, int id, char *action);
void			die_message(t_rules *rules, int id);
void			full_message(t_rules *rules);

//monitor.c
void			*monitor5(void *ptr);
void			*monitor6(void *ptr);

//parser.c
unsigned long	get_time(void);
int				parse_args(int argc, char **argv, t_rules *rules);

//ft_usleep.c
void			ft_usleep(unsigned long usec);
void			ft_usleep_zombie(unsigned long usec, t_philos *philo);

#endif
