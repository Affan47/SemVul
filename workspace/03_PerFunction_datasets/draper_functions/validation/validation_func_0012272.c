ay_aim_get_states()
{
	LList *states = NULL;
	LOG(("ay_aim_get_states ()"))

		states = l_list_append(states, "Online");
	states = l_list_append(states, "Away");
	states = l_list_append(states, "Offline");

	return states;
}
