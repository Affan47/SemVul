synaptics_rmi4_resume(struct device *dev)
{
	int retval;
	unsigned char intr_status;
	struct synaptics_rmi4_data *rmi4_data = dev_get_drvdata(dev);

	retval = regulator_enable(rmi4_data->regulator);
	if (retval) {
		dev_err(dev, "Regulator enable failed (%d)\n", retval);
		return retval;
	}

	enable_irq(rmi4_data->i2c_client->irq);
	rmi4_data->touch_stopped = false;

	retval = synaptics_rmi4_i2c_block_read(rmi4_data,
				rmi4_data->fn01_data_base_addr + 1,
				&intr_status,
				rmi4_data->number_of_interrupt_register);
	if (retval < 0)
		return retval;

	retval = synaptics_rmi4_i2c_byte_write(rmi4_data,
					rmi4_data->fn01_ctrl_base_addr + 1,
					(intr_status | TOUCHPAD_CTRL_INTR));
	if (retval < 0)
		return retval;

	return 0;
}
