nec_set_irq_line(int irqline, int state)
{
	if (irqline == IRQ_LINE_NMI)
	{
		if( I.nmi_state == state ) return;
	    I.nmi_state = state;
		if (state != CLEAR_LINE)
		{
			I.pending_irq |= NMI_IRQ;
		}
	}
	else
	{
		I.irq_state = state;
		if (state == CLEAR_LINE)
		{

				I.pending_irq &= ~INT_IRQ;
		}
		else
		{

				I.pending_irq |= INT_IRQ;
		}
	}
}
