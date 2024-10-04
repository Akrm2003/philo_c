/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 01:49:08 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/10/04 04:20:27 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_utils(t_philo *philo, char *str)
{
	if (died(philo))
		return (1);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%d %ld %s\n", get_time() - philo->start, philo->index + 1, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

int	ft_print(int flag, t_philo *philo)
{
	if (flag == 1)
		return (ft_print_utils(philo, "has taken a fork"));
	else if (flag == 2)
		return (ft_print_utils(philo, "is eating"));
	else if (flag == 3)
		return (ft_print_utils(philo, "is sleeping"));
	else if (flag == 4)
		return (ft_print_utils(philo, "is thinking"));
	return (0);
}
