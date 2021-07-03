#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# define ERROR_ALLOCATE "failed to allocate memory"
# define ERROR_MUTEX "mutex is not initialized"
# define ERROR_NUM_ARGS "wrong number of arguments"
# define ERROR_VAL_ARGS "wrong argument values"
# define ERROR_THREAD "failed to create thread"
# define ERROR_DETACH "failed to detach thread"
# define PHILO_EAT "is eating"
# define PHILO_SLEEP "is sleeping"
# define PHILO_THINK "is thinking"
# define PHILO_FORK "has taken a fork"
# define PHILO_DIE "died"

typedef struct s_info
{
	long			start_time;
	int				stop;
	pthread_mutex_t	*forks;
	unsigned int	num_of_philos;
	unsigned int	time_to_live;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
}	t_info;

typedef struct s_philo
{
	pthread_t		philo;
	unsigned int	philo_num;
	unsigned int	left_fork;
	unsigned int	right_fork;
	unsigned int	eat_count;
	long			time_last_meal;
	t_info			*s_info;
}	t_philo;

typedef struct s_main
{
	t_philo			*s_philos;
	int				num_must_eat;
}	t_main;

int		ft_strlen(char *str);
int		put_error(char *err);
long	get_cur_time(long start_time);
void	print_state(t_info *s_info, unsigned int num, char *state);
int		check_argv(char *str_arg);
int		set_args(t_main *s_main, t_info *s_info, int argc, char *argv[]);
int		init_philos(t_main *s_main, t_info *s_info);
int		init_forks(t_info *s_info);
void	check_death(t_main *s_main, t_info *s_info);
int		start_philos(t_main *s_main, t_info *s_info);
void	clean_and_destroy(t_main *s_main, t_info *s_info);

#endif
