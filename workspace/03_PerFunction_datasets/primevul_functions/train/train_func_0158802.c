static int __init elevator_setup(char *str)
{


	strncpy(chosen_elevator, str, sizeof(chosen_elevator) - 1);
	return 1;
}
