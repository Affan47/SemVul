pch_uart_verify_port(struct uart_port *port,
				struct serial_struct *serinfo)
{
	struct eg20t_port *priv;

	priv = container_of(port, struct eg20t_port, port);
	if (serinfo->flags & UPF_LOW_LATENCY) {
		dev_info(priv->port.dev,
			"PCH UART : Use PIO Mode (without DMA)\n");
		priv->use_dma = 0;
		serinfo->flags &= ~UPF_LOW_LATENCY;
	} else {
#ifndef CONFIG_PCH_DMA
		dev_err(priv->port.dev, "%s : PCH DMA is not Loaded.\n",
			__func__);
		return -EOPNOTSUPP;
#endif
		if (!priv->use_dma) {
			pch_request_dma(port);
			if (priv->chan_rx)
				priv->use_dma = 1;
		}
		dev_info(priv->port.dev, "PCH UART: %s\n",
				priv->use_dma ?
				"Use DMA Mode" : "No DMA");
	}

	return 0;
}
