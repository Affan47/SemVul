void clock_was_set(void)
{

	on_each_cpu(retrigger_next_event, NULL, 0, 1);
}
