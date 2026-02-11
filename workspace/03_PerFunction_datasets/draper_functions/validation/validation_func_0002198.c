mei_me_set_pm_domain(struct mei_device *dev)
{
	struct pci_dev *pdev  = to_pci_dev(dev->dev);

	if (pdev->dev.bus && pdev->dev.bus->pm) {
		dev->pg_domain.ops = *pdev->dev.bus->pm;

		dev->pg_domain.ops.runtime_suspend = mei_me_pm_runtime_suspend;
		dev->pg_domain.ops.runtime_resume = mei_me_pm_runtime_resume;
		dev->pg_domain.ops.runtime_idle = mei_me_pm_runtime_idle;

		pdev->dev.pm_domain = &dev->pg_domain;
	}
}
