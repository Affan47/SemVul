void __init acpi_pic_sci_set_trigger(unsigned int irq, u16 trigger)
{
	unsigned int mask = 1 << irq;
	unsigned int old, new;


	old = inb(0x4d0) | (inb(0x4d1) << 8);


	new = acpi_noirq ? old : 0;


	switch (trigger) {
	case 1:
		new &= ~mask;
		break;
	case 3:
		new |= mask;
		break;
	}

	if (old == new)
		return;

	printk(PREFIX "setting ELCR to %04x (from %04x)\n", new, old);
	outb(new, 0x4d0);
	outb(new >> 8, 0x4d1);
}
