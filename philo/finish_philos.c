#include "philosophers.h"

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
	printf("ALL POKUSHALI\n");
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
				break ;
		}
		if (i == s_info->num_of_philos)
			i = 0;
		cur_time = get_cur_time(s_info->start_time);
		if (cur_time > s_main->s_philos[i].time_last_meal + s_info->time_to_live)
			break ;
		i++;
	}
	print_state(s_info, s_main->s_philos[i].philo_num, PHILO_DIE);
	exit(0); // detach or clean here
	// printf("%d - SDOOOOOOH!\n", s_main->s_philos[i].philo_num);
	// printf("last_meal - %ld, cur_time - %ld\n", s_main->s_philos[i].time_last_meal, cur_time);
}
