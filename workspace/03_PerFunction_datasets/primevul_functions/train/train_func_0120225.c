void select_default_activity(struct activity *act[])
{
	int p;

	p = get_activity_position(act, A_CPU, EXIT_IF_NOT_FOUND);


	if (!get_activity_nr(act, AO_SELECTED, COUNT_ACTIVITIES)) {


		act[p]->options |= AO_SELECTED;
	}


	if (!count_bits(cpu_bitmap.b_array, BITMAP_SIZE(cpu_bitmap.b_size))) {
		cpu_bitmap.b_array[0] |= 0x01;
	}
}
