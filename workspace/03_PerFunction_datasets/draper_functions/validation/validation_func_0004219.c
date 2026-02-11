snd_mpu401_uart_free(struct snd_rawmidi *rmidi)
{
	struct snd_mpu401 *mpu = rmidi->private_data;
	if (mpu->irq >= 0)
		free_irq(mpu->irq, (void *) mpu);
	release_and_free_resource(mpu->res);
	kfree(mpu);
}
