nouveau_vga_fini(struct nouveau_drm *drm)
{
	struct drm_device *dev = drm->dev;
	bool runtime = false;

	if (nouveau_runtime_pm == 1)
		runtime = true;
	if ((nouveau_runtime_pm == -1) && (nouveau_is_optimus() || nouveau_is_v1_dsm()))
		runtime = true;

	vga_switcheroo_unregister_client(dev->pdev);
	if (runtime && nouveau_is_v1_dsm() && !nouveau_is_optimus())
		vga_switcheroo_fini_domain_pm_ops(drm->dev->dev);
	vga_client_register(dev->pdev, NULL, NULL, NULL);
}
