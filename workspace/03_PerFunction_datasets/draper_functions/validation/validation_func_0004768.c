pch_uart_pci_probe(struct pci_dev *pdev,
					const struct pci_device_id *id)
{
	int ret;
	struct eg20t_port *priv;

	ret = pci_enable_device(pdev);
	if (ret < 0)
		goto probe_error;

	priv = pch_uart_init_port(pdev, id);
	if (!priv) {
		ret = -EBUSY;
		goto probe_disable_device;
	}
	pci_set_drvdata(pdev, priv);

	return ret;

probe_disable_device:
	pci_disable_msi(pdev);
	pci_disable_device(pdev);
probe_error:
	return ret;
}
