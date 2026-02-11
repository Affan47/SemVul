sht15_interrupt_fired(int irq, void *d)
{
	struct sht15_data *data = d;


	disable_irq_nosync(irq);
	atomic_inc(&data->interrupt_handled);

	if (data->state != SHT15_READING_NOTHING)
		schedule_work(&data->read_work);
	return IRQ_HANDLED;
}
