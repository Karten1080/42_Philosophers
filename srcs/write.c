/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:01:44 by asmati            #+#    #+#             */
/*   Updated: 2025/12/23 17:01:44 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	write_status_debug(t_philo_status status, t_philo *philo,
		long elapsed)
{
	if (TAKE_FIRST_FORK == status && !simulation_finish(philo->table))
		printf(W "%6ld" RST " %d has taken the 1° fork 😋"
			"\t\t\tn°" B "[🍴 %d 🍴]\n" RST,
			elapsed,
			philo->id,
			philo->first_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && !simulation_finish(philo->table))
		printf(W "%6ld" RST " %d has taken the 2° fork  😋"
			"\t\t\tn°" RED "[🍴 %d 🍴]\n" RST,
			elapsed,
			philo->id,
			philo->second_fork->fork_id);
	else if (EATING == status && !simulation_finish(philo->table))
		printf(W "%6ld" RST " %d is eating 🍜"
			"\t\t\tn°" B "[🍜 %ld 🍜]\n" RST,
			elapsed,
			philo->id,
			philo->meals_counter);
	else if (SLEEPING == status && !simulation_finish(philo->table))
		printf(W "%6ld" RST " %d is sleeping 💤\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finish(philo->table))
		printf(W "%6ld" RST " %d is thinking 🤔\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED "\t\t %6ld  %d died \n" RST, elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finish(philo->table))
			printf(W "%-6ld" RST " %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !simulation_finish(philo->table))
			printf(W "%-6ld" RST " %d is eating\n", elapsed, philo->id);
		else if (SLEEPING == status && !simulation_finish(philo->table))
			printf(W "%-6ld" RST " %d is sleeping\n", elapsed, philo->id);
		else if (DIED == status)
			printf(W "%-6ld" RST " %d died\n", elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
