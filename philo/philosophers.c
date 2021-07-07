#include "philosophers.h"

int	main(int argc, char *argv[])
{
	int				state;
	int				stop;
	t_main			s_main;
	t_info			s_info;
	pthread_mutex_t	lock;

	s_info.lock = &lock;
	s_info.stop = &stop;
	pthread_mutex_init(s_info.lock, NULL);
	if (argc < 5 || argc > 6)
		return (put_error(ERROR_NUM_ARGS));
	if (set_args(&s_main, &s_info, argc, argv))
		return (1);
	if (init_philos(&s_main, &s_info) || init_forks(&s_info))
		return (1);
	state = start_philos(&s_main, &s_info);
	clean_and_destroy(&s_main, &s_info);
	return (state);
}
