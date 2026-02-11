mlx4_free_ownership(struct mlx4_dev *dev)
{
	void __iomem *owner;

	if (pci_channel_offline(dev->persist->pdev))
		return;

	owner = ioremap(pci_resource_start(dev->persist->pdev, 0) +
			MLX4_OWNER_BASE,
			MLX4_OWNER_SIZE);
	if (!owner) {
		mlx4_err(dev, "Failed to obtain ownership bit\n");
		return;
	}
	writel(0, owner);
	msleep(1000);
	iounmap(owner);
}
