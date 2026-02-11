sis_get_driver(struct agp_bridge_data *bridge)
{
	int i;

	for (i=0; sis_broken_chipsets[i]!=0; ++i)
		if (bridge->dev->device==sis_broken_chipsets[i])
			break;

	if (sis_broken_chipsets[i] || agp_sis_force_delay)
		sis_driver.agp_enable=sis_delayed_enable;


	if ((agp_bridge->major_version == 3 && agp_bridge->minor_version >= 5
	     && agp_sis_agp_spec!=0) || agp_sis_agp_spec==1) {
		sis_driver.aperture_sizes = agp3_generic_sizes;
		sis_driver.size_type = U16_APER_SIZE;
		sis_driver.num_aperture_sizes = AGP_GENERIC_SIZES_ENTRIES;
		sis_driver.configure = agp3_generic_configure;
		sis_driver.fetch_size = agp3_generic_fetch_size;
		sis_driver.cleanup = agp3_generic_cleanup;
		sis_driver.tlb_flush = agp3_generic_tlbflush;
	}
}
