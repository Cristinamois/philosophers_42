/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmois <cmois@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:10:36 by cmois             #+#    #+#             */
/*   Updated: 2022/02/13 13:14:39 by cmois            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define PL_STATE_FORK  "has taken a fork"
# define PL_STATE_EAT   "is eating"
# define PL_STATE_SLEEP "is sleeping"
# define PL_STATE_THINK "is thinking"
# define PL_STATE_DIE   "died"

/*
   number_of_philosophers							0
   time_to_die										1
   time_to_eat										2
   time_to_sleep									3
   [number_of_times_each_philosopher_must_eat]		4
 */

/*
   blabla			0
   miam				1
   end				2

 */

/*
	timestamp_in_ms X has taken a fork
	timestamp_in_ms X is eating
	timestamp_in_ms X is sleeping
	timestamp_in_ms X is thinking
	timestamp_in_ms X died
 */

typedef struct s_philosopher
{
	struct s_pl	*pl;
	int			id;
	int			lfid;
	int			rfid;
	pthread_t	t1id;
	long		last_ate_time;
	long		ate_food;
	bool		had_enough_food;
}				t_philosopher;

typedef struct s_pl
{
	long			subject[5];
	pthread_mutex_t	mutexes[4];
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	struct timeval	start_time;
	int				flag;
	long			i;

}				t_pl;

/*		INIT		*/
bool		init_mutexes(t_pl *pl);
bool		init_philos(t_pl *pl);
bool		init(t_pl *pl);
int			__getflag(t_pl *pl);
int			__setflag(t_philosopher *p, int new_val);
/*		PARSER		*/
bool		parser(t_pl *pl, int ac, char *av[]);
/*		UTILS		*/
long int	__gettime(t_pl *pl);
void		__usleep(long int time, t_pl *pl);
void		*malloc_and_memset(size_t size);
bool		is_char_digit(int c);
bool		is_str_numeric(char *str);
long		str_to_long(char *str);
/*		DO THE JOB	*/
void		put_philo_state(t_philosopher *p, char *state);
void		take_forks(t_philosopher *p);
void		eat(t_philosopher *p);
void		sleep_and_think(t_philosopher *p);
/*		CHECK PHILO	*/
bool		is_philo_bigboi(t_philosopher *p);
bool		is_philo_deadboi(t_philosopher *p);
void		single_monitor(t_pl *pl);
/*		ROUTINE		*/
void		thread_creation(t_pl *pl);
void		*routine1(void *arg);
void		*routine2(void *arg);
/*		DESTROY		*/
void		destroy_all(t_pl *pl);
#endif
