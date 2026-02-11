safe_to_load (void)
{
	struct mem_range *mem_range = state.mem_range;
	while (mem_range)
	{
		if (cpunum_read_byte (mem_range->cpu, mem_range->addr) !=
			mem_range->start_value)
		{
			return 0;
		}
		if (cpunum_read_byte (mem_range->cpu, mem_range->addr + mem_range->num_bytes - 1) !=
			mem_range->end_value)
		{
			return 0;
		}
		mem_range = mem_range->next;
	}
	return 1;
}
