static bool __ref get_trap_addr(void **addr, unsigned int ist)
{
	unsigned int nr;
	bool ist_okay = false;


	for (nr = 0; nr < ARRAY_SIZE(trap_array); nr++) {
		struct trap_array_entry *entry = trap_array + nr;

		if (*addr == entry->orig) {
			*addr = entry->xen;
			ist_okay = entry->ist_okay;
			break;
		}
	}

	if (nr == ARRAY_SIZE(trap_array) &&
	    *addr >= (void *)early_idt_handler_array[0] &&
	    *addr < (void *)early_idt_handler_array[NUM_EXCEPTION_VECTORS]) {
		nr = (*addr - (void *)early_idt_handler_array[0]) /
		     EARLY_IDT_HANDLER_SIZE;
		*addr = (void *)xen_early_idt_handler_array[nr];
	}

	if (WARN_ON(ist != 0 && !ist_okay))
		return false;

	return true;
}
