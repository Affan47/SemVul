get_diskdump_panic_task(void)
{
	int i;

	if ((!DISKDUMP_VALID() && !KDUMP_CMPRS_VALID())
	    || !get_active_set())
		return NO_TASK;

	if (DISKDUMP_VALID())
		return (ulong)dd->header->tasks[dd->header->current_cpu];

	if (KDUMP_CMPRS_VALID()) {
		if (kernel_symbol_exists("crashing_cpu") &&
		    cpu_map_addr("online")) {
			get_symbol_data("crashing_cpu", sizeof(int), &i);
			if ((i >= 0) && in_cpu_map(ONLINE, i)) {
				if (CRASHDEBUG(1))
					error(INFO, "get_diskdump_panic_task: "
					    "active_set[%d]: %lx\n",
						i, tt->active_set[i]);
				return (tt->active_set[i]);
			}
		}
	}

	return NO_TASK;
}
