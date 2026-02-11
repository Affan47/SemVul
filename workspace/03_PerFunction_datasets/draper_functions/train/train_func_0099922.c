update_irq_state(void)
{


	data16_t irq = metro_irq_cause_r(0,0) & ~*metro_irq_enable;

	if (irq_line == -1)
	{


		int i = 0;
		while ( i < 8 )
		{
			if (irq & (1 << i))
			{
				cpu_set_irq_line(0, metro_irq_levels[i]&7, ASSERT_LINE);
				return;
			}
			i++;
		}
		cpu_set_irq_line(0, 0, ASSERT_LINE);
	}
	else
	{


		int state =	(irq ? ASSERT_LINE : CLEAR_LINE);
		cpu_set_irq_line(0, irq_line, state);
	}
}
