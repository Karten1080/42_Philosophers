/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:17:34 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/23 19:31:49 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../libft/includes/libft.h"
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RST "\033[0m"
# define RED "\033[31m"
# define G "\033[32m"
# define Y "\033[33m"
# define B "\033[34m"
# define M "\033[35m"
# define C "\033[36m"
# define W "\033[37m"

// Macro write fonction macro
# define DEBUG_MODE 1
// ** OPCODE FOR MUTEX | thread functions ** //
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

typedef enum e_time_code
{
	SECOND,
	MICROSECOND,
	MILLISECOND,
}						t_time_code;

typedef pthread_mutex_t	t_mtx;

typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;

}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_mtx				philo_mutex;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				start_simulation;
	long				threads_running_nbr;
	bool				end_simulation;
	bool				all_threads_ready;
	pthread_t			monitor;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
	t_fork				*forks;
	t_philo				*philos;
}						t_table;

// *** Prototypes *** //

// ** Utils ** //
void					error_exit(const char *error);
long					gettime(t_time_code time_code);
void					precise_usleep(long usec, t_table *table);
void					clean(t_table *table);

// ** Parcings ** //
void					parse_input(t_table *table, char **av);
bool					is_space(char c);
bool					is_digit(char c);

// ** Safe_fonctions ** //
void					safe_thread_handle(pthread_t *thread,
							void *(*start_routine)(void *), void *data,
							t_opcode opcode);
void					safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void					*safe_malloc(size_t bytes);

// ** Unit ** //
void					data_init(t_table *table);

// ** Dinner ** //
void					*dinner_simulation(void *data);
void					dinner_start(t_table *table);
void					*lone_philo(void *arg);
void					thinking(t_philo *philo, bool pre_simultation);

// ** Syncro Utils ** //
void					wait_all_threads(t_table *table);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long philo_nbr);
void					increase_long(t_mtx *mutex, long *value);

// ** Getters_Setters ** //
bool					simulation_finish(t_table *table);
bool					get_bool(t_mtx *mutex, bool *value);
void					set_bool(t_mtx *mutex, bool *dest, bool value);
void					set_long(t_mtx *mutex, long *dest, long value);
long					get_long(t_mtx *mutex, long *value);

// ** Write ** //
void					write_status(t_philo_status stqtus, t_philo *philo,
							bool debug);
void					de_synchronize_philos(t_philo *philo);
// ** Monitor ** //
void					*monitor_dinner(void *data);

#endif
