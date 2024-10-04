/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 01:43:43 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/10/05 01:54:25 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	time;
	long			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

int	died(t_philo *philo)
{
	if (philo->eating_nums != -1 && philo->eating_nums == 0)
		return (1);
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	if (get_time() - philo->last_eat >= philo->time_to_die)
	{
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->dead_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%d %ld died\n", get_time() - philo->start, philo->index + 1);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (0);
}

int	ft_usleep(long time, t_philo *philo)
{
	long	start;
	long	end;

	start = get_time();
	end = start + time;
	while (get_time() < end)
	{
		if (died(philo))
			return (1);
		usleep(250);
	}
	return (0);
}

t_philo	*f_init(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	philo->start = get_time();
	philo->last_eat = philo->start;
	if (philo->index == 0)
	{
		philo->left = philo->data->number_of_philosophers - 1;
		philo->right = philo->index;
	}
	else
	{
		philo->left = philo->index - 1;
		philo->right = philo->index;
	}
	if (philo->data->number_of_philosophers == 1)
	{
		ft_usleep(philo->time_to_die, philo);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%d %ld died\n", get_time() - philo->start, philo->index + 1);
		pthread_mutex_unlock(&philo->data->print_mutex);
		philo->data->is_dead = 1;
	}
	return (philo);
}
