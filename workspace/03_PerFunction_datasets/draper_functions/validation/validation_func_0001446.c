test_tape_increase_current_value (void)
{
	CattleTape *tape;
	gint i;

	tape = cattle_tape_new ();

	for (i = 0; i < 128; i++) {

		g_assert (cattle_tape_get_current_value (tape) == i);
		cattle_tape_increase_current_value (tape);
	}

	cattle_tape_decrease_current_value_by (tape, 128);
	g_assert (cattle_tape_get_current_value (tape) == 0);

	cattle_tape_increase_current_value_by (tape, 128 * 5);
	g_assert (cattle_tape_get_current_value (tape) == 0);

	g_object_unref (tape);
}
