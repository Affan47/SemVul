drv_generic_parport_toggle(const unsigned char bits, const int level, const unsigned long delay)
{
    unsigned char value1, value2;


    if (bits == 0)
	return;


    value1 = level ? bits : 0;
    value2 = level ? 0 : bits;


    value1 = bits & (value1 ^ PARPORT_CONTROL_INVERTED ^ inverted_control_bits);
    value2 = bits & (value2 ^ PARPORT_CONTROL_INVERTED ^ inverted_control_bits);

#ifdef WITH_PPDEV
    if (PPdev) {
	struct ppdev_frob_struct frob;
	frob.mask = bits;


	frob.val = value1;
	ioctl(PPfd, PPFCONTROL, &frob);


	ndelay(delay);


	frob.val = value2;
	ioctl(PPfd, PPFCONTROL, &frob);

    }
#endif

#ifdef WITH_OUTB
    if (Port) {

	ctr = (ctr & ~bits) ^ value1;
	outb(ctr, Port + 2);


	ndelay(delay);


	ctr = (ctr & ~bits) ^ value2;
	outb(ctr, Port + 2);
    }
#endif
}
