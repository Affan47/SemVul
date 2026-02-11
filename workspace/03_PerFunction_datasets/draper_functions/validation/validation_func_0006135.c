mthca_free_irqs(struct mthca_dev *dev)
{
	int i;

	if (dev->eq_table.have_irq)
		free_irq(dev->pdev->irq, dev);
	for (i = 0; i < MTHCA_NUM_EQ; ++i)
		if (dev->eq_table.eq[i].have_irq) {
			free_irq(dev->eq_table.eq[i].msi_x_vector,
				 dev->eq_table.eq + i);
			dev->eq_table.eq[i].have_irq = 0;
		}
}
