intel_irq_remapping_alloc(struct irq_domain *domain,
				     unsigned int virq, unsigned int nr_irqs,
				     void *arg)
{
	struct intel_iommu *iommu = domain->host_data;
	struct irq_alloc_info *info = arg;
	struct intel_ir_data *data, *ird;
	struct irq_data *irq_data;
	struct irq_cfg *irq_cfg;
	int i, ret, index;

	if (!info || !iommu)
		return -EINVAL;
	if (nr_irqs > 1 && info->type != X86_IRQ_ALLOC_TYPE_MSI &&
	    info->type != X86_IRQ_ALLOC_TYPE_MSIX)
		return -EINVAL;


	if (info->type == X86_IRQ_ALLOC_TYPE_MSI)
		info->flags &= ~X86_IRQ_ALLOC_CONTIGUOUS_VECTORS;

	ret = irq_domain_alloc_irqs_parent(domain, virq, nr_irqs, arg);
	if (ret < 0)
		return ret;

	ret = -ENOMEM;
	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		goto out_free_parent;

	down_read(&dmar_global_lock);
	index = alloc_irte(iommu, virq, &data->irq_2_iommu, nr_irqs);
	up_read(&dmar_global_lock);
	if (index < 0) {
		pr_warn("Failed to allocate IRTE\n");
		kfree(data);
		goto out_free_parent;
	}

	for (i = 0; i < nr_irqs; i++) {
		irq_data = irq_domain_get_irq_data(domain, virq + i);
		irq_cfg = irqd_cfg(irq_data);
		if (!irq_data || !irq_cfg) {
			ret = -EINVAL;
			goto out_free_data;
		}

		if (i > 0) {
			ird = kzalloc(sizeof(*ird), GFP_KERNEL);
			if (!ird)
				goto out_free_data;

			ird->irq_2_iommu = data->irq_2_iommu;
			ird->irq_2_iommu.sub_handle = i;
		} else {
			ird = data;
		}

		irq_data->hwirq = (index << 16) + i;
		irq_data->chip_data = ird;
		irq_data->chip = &intel_ir_chip;
		intel_irq_remapping_prepare_irte(ird, irq_cfg, info, index, i);
		irq_set_status_flags(virq + i, IRQ_MOVE_PCNTXT);
	}
	return 0;

out_free_data:
	intel_free_irq_resources(domain, virq, i);
out_free_parent:
	irq_domain_free_irqs_common(domain, virq, nr_irqs);
	return ret;
}
