module_remove_driver(struct device_driver *drv)
{
	struct module_kobject *mk = NULL;
	char *driver_name;

	if (!drv)
		return;

	sysfs_remove_link(&drv->p->kobj, "module");

	if (drv->owner)
		mk = &drv->owner->mkobj;
	else if (drv->p->mkobj)
		mk = drv->p->mkobj;
	if (mk && mk->drivers_dir) {
		driver_name = make_driver_name(drv);
		if (driver_name) {
			sysfs_remove_link(mk->drivers_dir, driver_name);
			kfree(driver_name);
		}
	}
}
