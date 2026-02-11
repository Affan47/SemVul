update_irq_state(struct YMZ280BChip *chip)
{
	int irq_bits = chip->status_register & chip->irq_mask;


	if (!chip->irq_enable)
		irq_bits = 0;


	if (irq_bits && !chip->irq_state)
	{
		chip->irq_state = 1;
		if (chip->irq_callback)
			(*chip->irq_callback)(1);
else logerror("ymz280 irq_callback = 0");
	}
	else if (!irq_bits && chip->irq_state)
	{
		chip->irq_state = 0;
		if (chip->irq_callback)
			(*chip->irq_callback)(0);
else logerror("ymz280 irq_callback = 0");
	}
}
