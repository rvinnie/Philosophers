#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_main	s_main;
	t_info	s_info;

	if (argc < 5 || argc > 6)
		return (put_error(ERROR_NUM_ARGS));
	if (set_args(&s_main, &s_info, argc, argv) == -1)
		return (put_error(ERROR_VAL_ARGS));
	// printf("%d %d %d %d %d\n", s_main.num_of_philos, s_main.time_to_die, s_main.time_to_eat, s_main.time_to_sleep, s_main.num_must_eat);
	if (init_philos(&s_main, &s_info) || init_forks(&s_info))
		return (1);
	start_philos(&s_main, &s_info);
	return (0);
}
