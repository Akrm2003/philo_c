/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:44:46 by louisalah         #+#    #+#             */
/*   Updated: 2024/10/05 02:25:43 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data_help(t_data *data, char **av, int ac)
{
	data->is_dead = 0;
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->eating_nums = ft_atoi(av[5]);
	else
		data->eating_nums = -1;
}

void	init_data(t_data *data, char **av, int ac)
{
	int	i;

	i = -1;
	init_data_help(data, av, ac);
	data->forks = (int *)malloc(sizeof(int) * data->number_of_philosophers);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->read_dead_mutex, NULL);
	data->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	while (++i < data->number_of_philosophers)
	{
		if (i == 0 || i == data->number_of_philosophers - 1)
			data->forks[i] = data->number_of_philosophers - 1;
		else if (i % 2 == 0)
			data->forks[i] = i + 1;
		else
			data->forks[i] = i;
		pthread_mutex_init(&data->fork_mutex[i], NULL);
	}
}

t_philo	**init_philo(t_data *data)
{
	int		i;
	t_philo	**philo;

	i = -1;
	philo = (t_philo **)malloc(sizeof(t_philo *)
			* data->number_of_philosophers);
	while (++i < data->number_of_philosophers)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->index = i;
		philo[i]->time_to_die = data->time_to_die;
		philo[i]->time_to_eat = data->time_to_eat;
		philo[i]->time_to_sleep = data->time_to_sleep;
		philo[i]->eating_nums = data->eating_nums;
		philo[i]->data = data;
	}
	return (philo);
}

void	free_all(t_data *data, t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
		free(philo[i]);
	free(philo);
	free(data->forks);
	free(data->fork_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->read_dead_mutex);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		**philo;
	int			i;

	i = -1;
	if (ac > 6 || ac < 5)
		(write(2, "Error: Wrong number of arguments\n", 33), exit(1));
	check_input(ac, av);
	init_data(&data, av, ac);
	philo = init_philo(&data);
	while (++i < data.number_of_philosophers)
		pthread_create(&philo[i]->thread, NULL, &routine, (void *)philo[i]);
	i = -1;
	while (++i < data.number_of_philosophers)
		pthread_join(philo[i]->thread, NULL);
	free_all(&data, philo);
}
