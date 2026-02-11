io_apic_modify_irq(struct mp_chip_data *data,
			       int mask_and, int mask_or,
			       void (*final)(struct irq_pin_list *entry))
{
	union entry_union eu;
	struct irq_pin_list *entry;

	eu.entry = data->entry;
	eu.w1 &= mask_and;
	eu.w1 |= mask_or;
	data->entry = eu.entry;

	for_each_irq_pin(entry, data->irq_2_pin) {
		io_apic_write(entry->apic, 0x10 + 2 * entry->pin, eu.w1);
		if (final)
			final(entry);
	}
}
