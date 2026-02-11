joy_flush()
{
	int                     i;
	joy_button_info *bi;

	if ( joy_num_sticks < 1 )
		return;

	for ( i = 0; i < JOY_TOTAL_BUTTONS; i++) {
		bi = &joy_buttons[i];
		bi->actual_state = 0;
		bi->state = 0;
		bi->down_count = 0;
		bi->up_count = 0;
		bi->down_time = 0;
		bi->last_down_check = timer_get_milliseconds();
	}
}
