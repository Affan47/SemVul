v60_set_irq_line(int irqline, int state)
{
	if(irqline == IRQ_LINE_NMI) {
		switch(state) {
		case ASSERT_LINE:
			if(v60.nmi_line == CLEAR_LINE) {
				v60.nmi_line = ASSERT_LINE;
				v60_do_irq(2);
			}
			break;
		case CLEAR_LINE:
			v60.nmi_line = CLEAR_LINE;
			break;
		case HOLD_LINE:
		case PULSE_LINE:
			v60.nmi_line = CLEAR_LINE;
			v60_do_irq(2);
			break;
		}
	} else {
		v60.irq_line = state;
		v60_try_irq();
	}
}
