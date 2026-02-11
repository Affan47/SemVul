pas_midi_open(int dev, int mode,
	      void            (*input) (int dev, unsigned char data),
	      void            (*output) (int dev)
)
{
	int             err;
	unsigned long   flags;
	unsigned char   ctrl;


	if (midi_busy)
		return -EBUSY;


	pas_write(0x20 | 0x40,
		  0x178b);

	spin_lock_irqsave(&pas_lock, flags);

	if ((err = pas_set_intr(0x10)) < 0)
	{
		spin_unlock_irqrestore(&pas_lock, flags);
		return err;
	}


	ctrl = 0;
	input_opened = 0;
	midi_input_intr = input;

	if (mode == OPEN_READ || mode == OPEN_READWRITE)
	{
		ctrl |= 0x04;
		input_opened = 1;
	}
	if (mode == OPEN_WRITE || mode == OPEN_READWRITE)
	{
		ctrl |= 0x08 | 0x10;
	}
	pas_write(ctrl, 0x178b);


	pas_write(0xff, 0x1B88);

	spin_unlock_irqrestore(&pas_lock, flags);

	midi_busy = 1;
	qlen = qhead = qtail = 0;
	return 0;
}
