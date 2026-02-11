asd_process_ctrla_phy_settings(struct asd_ha_struct *asd_ha,
					  struct asd_ctrla_phy_settings *ps)
{
	int i;
	for (i = 0; i < ps->num_phys; i++) {
		struct asd_ctrla_phy_entry *pe = &ps->phy_ent[i];

		if (!PHY_ENABLED(asd_ha, i))
			continue;
		if (*(u64 *)pe->sas_addr == 0) {
			asd_ha->hw_prof.enabled_phys &= ~(1 << i);
			continue;
		}

		memcpy(asd_ha->hw_prof.phy_desc[i].sas_addr, pe->sas_addr,
		       SAS_ADDR_SIZE);
		asd_ha->hw_prof.phy_desc[i].max_sas_lrate =
			(pe->sas_link_rates & 0xF0) >> 4;
		asd_ha->hw_prof.phy_desc[i].min_sas_lrate =
			(pe->sas_link_rates & 0x0F);
		asd_ha->hw_prof.phy_desc[i].max_sata_lrate =
			(pe->sata_link_rates & 0xF0) >> 4;
		asd_ha->hw_prof.phy_desc[i].min_sata_lrate =
			(pe->sata_link_rates & 0x0F);
		asd_ha->hw_prof.phy_desc[i].flags = pe->flags;
		ASD_DPRINTK("ctrla: phy%d: sas_addr: %llx, sas rate:0x%x-0x%x,"
			    " sata rate:0x%x-0x%x, flags:0x%x\n",
			    i,
			    SAS_ADDR(asd_ha->hw_prof.phy_desc[i].sas_addr),
			    asd_ha->hw_prof.phy_desc[i].max_sas_lrate,
			    asd_ha->hw_prof.phy_desc[i].min_sas_lrate,
			    asd_ha->hw_prof.phy_desc[i].max_sata_lrate,
			    asd_ha->hw_prof.phy_desc[i].min_sata_lrate,
			    asd_ha->hw_prof.phy_desc[i].flags);
	}

	return 0;
}
