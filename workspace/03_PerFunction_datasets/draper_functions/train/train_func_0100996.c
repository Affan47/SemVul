max3100_enable_ms(struct uart_port *port)
{
	struct max3100_port *s = container_of(port,
					      struct max3100_port,
					      port);

	if (s->poll_time > 0)
		mod_timer(&s->timer, jiffies);
	dev_dbg(&s->spi->dev, "%s\n", __func__);
}
