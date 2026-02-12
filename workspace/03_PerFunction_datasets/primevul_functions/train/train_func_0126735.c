static void send_pulse_homebrew_softcarrier(unsigned int length, ktime_t edge)
{
	ktime_t now, target = ktime_add_us(edge, length);


	s32 delta;
	unsigned int pulse, space;


	pulse = DIV_ROUND_CLOSEST(serial_ir.duty_cycle * (NSEC_PER_SEC / 100),
				  serial_ir.carrier);
	space = DIV_ROUND_CLOSEST((100 - serial_ir.duty_cycle) *
				  (NSEC_PER_SEC / 100), serial_ir.carrier);

	for (;;) {
		now = ktime_get();
		if (ktime_compare(now, target) >= 0)
			break;
		on();
		edge = ktime_add_ns(edge, pulse);
		delta = ktime_to_ns(ktime_sub(edge, now));
		if (delta > 0)
			ndelay(delta);
		now = ktime_get();
		off();
		if (ktime_compare(now, target) >= 0)
			break;
		edge = ktime_add_ns(edge, space);
		delta = ktime_to_ns(ktime_sub(edge, now));
		if (delta > 0)
			ndelay(delta);
	}
}
