rapl_remove_package(struct rapl_package *rp)
{
	struct rapl_domain *rd, *rd_package = NULL;

	for (rd = rp->domains; rd < rp->domains + rp->nr_domains; rd++) {
		if (rd->id == RAPL_DOMAIN_PACKAGE) {
			rd_package = rd;
			continue;
		}
		pr_debug("remove package %d, %s domain\n", rp->id, rd->name);
		powercap_unregister_zone(control_type, &rd->power_zone);
	}

	powercap_unregister_zone(control_type, &rd_package->power_zone);
	list_del(&rp->plist);
	kfree(rp);
}
