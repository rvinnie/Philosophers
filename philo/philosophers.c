#include "philosophers.h"

int	main(int argc, char *argv[])
{
	int		state;
	t_main	s_main;
	t_info	s_info;

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
