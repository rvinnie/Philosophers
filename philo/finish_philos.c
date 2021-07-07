#include "philosophers.h"

void	clean_and_destroy(t_main *s_main, t_info *s_info)
{
	int	num_of_philos;
	int	i;

	num_of_philos = (int)s_info->num_of_philos;
	i = 0;
	while (i < num_of_philos)
		pthread_mutex_destroy(&s_info->forks[i++]);
	free(s_info->forks);
	free(s_main->s_philos);
	pthread_mutex_destroy(s_info->lock);
}

int	check_eat_count(t_main *s_main, unsigned int num_of_philos)
{
	t_philo	*s_philos;
	int		num_must_eat;
	int		i;

	s_philos = s_main->s_philos;
	num_must_eat = s_main->num_must_eat;
	i = 0;
	while ((unsigned int)i < num_of_philos)
	{
		if ((int)s_philos[i].eat_count < num_must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	check_death(t_main *s_main, t_info *s_info)
{
	unsigned int	i;
	long			cur_time;

	i = 0;
	while (1 == 1)
	{
		if (s_main->num_must_eat != -1)
		{
			if (check_eat_count(s_main, s_info->num_of_philos) == 1)
			{
				*s_info->stop = 1;
				return ;
			}
		}
		if (i == s_info->num_of_philos)
			i = 0;
		cur_time = get_cur_time(s_info->start_time);
		if (cur_time > s_main->s_philos[i].time_last_meal
			+ s_info->time_to_live)
			break ;
		i++;
	}
	print_state(s_info, s_main->s_philos[i].philo_num, PHILO_DIE);
	*s_info->stop = 1;
}
