hypervisor_subsys_init(void)
{
	if (!xen_domain())
		return -ENODEV;

	hypervisor_kobj->ktype = &hyp_sysfs_kobj_type;
	return 0;
}
