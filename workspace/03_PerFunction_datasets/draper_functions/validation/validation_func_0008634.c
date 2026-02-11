tms34010_set_irq_line(int irqline, int linestate)
{
	LOG(("TMS34010#%d set irq line %d state %d\n", cpu_getactivecpu(), irqline, linestate));


	switch (irqline)
	{
		case 0:
			if (linestate != CLEAR_LINE)
			{
				state.ext_irq_lines |= 1;
				IOREG(REG_INTPEND) |= TMS34010_INT1;
			}
			else
			{
				state.ext_irq_lines &= ~1;
				IOREG(REG_INTPEND) &= ~TMS34010_INT1;
			}
			break;

		case 1:
			if (linestate != CLEAR_LINE)
			{
				state.ext_irq_lines |= 2;
				IOREG(REG_INTPEND) |= TMS34010_INT2;
			}
			else
			{
				state.ext_irq_lines &= ~2;
				IOREG(REG_INTPEND) &= ~TMS34010_INT2;
			}
			break;
	}
	check_interrupt();
}
