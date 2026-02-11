slidebar_mode_get(void)
{
	u8 res;
	unsigned long flags;

	spin_lock_irqsave(&io_lock, flags);
	outb(0xf7, 0xff29);
	outb(0x8b, 0xff2a);
	res = inb(0xff2b);
	spin_unlock_irqrestore(&io_lock, flags);

	return res;
}
