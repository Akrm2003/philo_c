/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:45:15 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/10/05 01:54:13 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_forks(t_philo *philo)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&philo->data->fork_mutex[philo->left]);
	if (philo->data->forks[philo->left] != philo->index)
		status++;
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->left]);
	pthread_mutex_lock(&philo->data->fork_mutex[philo->right]);
	if (philo->data->forks[philo->right] != philo->index)
		status++;
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->right]);
	return (status);
}

void	*routine_help(t_philo *philo)
{
	if (ft_print(1, philo) || ft_print(1, philo)
		|| ft_print(2, philo)
		|| ft_usleep(philo->time_to_eat, philo))
		return (NULL);
	philo->last_eat = get_time();
	pthread_mutex_lock(&philo->data->fork_mutex[philo->left]);
	philo->data->forks[philo->left] = philo->index;
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->left]);
	pthread_mutex_lock(&philo->data->fork_mutex[philo->right]);
	philo->data->forks[philo->right] = philo->index;
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->right]);
	if (ft_print(3, philo) || ft_usleep(philo->time_to_sleep, philo)
		|| ft_print(4, philo))
		return (NULL);
	philo->eating_nums--;
	return (philo);
}

void	*routine(void *p)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = f_init(p);
	while (!died(philo))
	{
		if ((philo->eating_nums == -1 || philo->eating_nums != 0))
		{
			if (check_forks(philo) == 2)
			{
				i = 1;
				if (routine_help(philo) == NULL)
					return (NULL);
			}
			else if (!i && i++)
				ft_usleep(philo->time_to_eat - 2, philo);
			else if (i == 1 && i++)
				ft_usleep(4, philo);
		}
	}
	return (NULL);
}
