static int fsl_lpspi_calculate_timeout(struct fsl_lpspi_data *fsl_lpspi,
				       int size)
{
	unsigned long timeout = 0;


	timeout = (8 + 4) * size / fsl_lpspi->config.speed_hz;


	timeout += 1;


	return msecs_to_jiffies(2 * timeout * MSEC_PER_SEC);
}
