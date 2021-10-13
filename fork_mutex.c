/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klever <klever@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:52:40 by klever            #+#    #+#             */
/*   Updated: 2021/10/13 18:42:10 by klever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	take_fork(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->left->fork);
	pthread_mutex_lock(philo->print);
	(*philo->num_fork)--;
	pthread_mutex_unlock(philo->print);
	print_status(philo, GREEN"has taken a fork");
	 if (philo->size_lst == 1)
		think_philo(philo);
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(philo->print);
	(*philo->num_fork)--;
	pthread_mutex_unlock(philo->print);
	print_status(philo, GREEN"has taken a fork");
}

void	free_fork(t_philosophers *philo)
{
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_lock(philo->print);
	(*philo->num_fork)++;
	pthread_mutex_unlock(philo->print);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_lock(philo->print);
	(*philo->num_fork)++;
	pthread_mutex_unlock(philo->print);
}