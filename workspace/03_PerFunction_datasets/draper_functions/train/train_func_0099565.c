mptsas_expander_event_add(MPT_ADAPTER *ioc,
    MpiEventDataSasExpanderStatusChange_t *expander_data)
{
	struct mptsas_portinfo *port_info;
	int i;
	__le64 sas_address;

	port_info = kzalloc(sizeof(struct mptsas_portinfo), GFP_KERNEL);
	if (!port_info)
		BUG();
	port_info->num_phys = (expander_data->NumPhys) ?
	    expander_data->NumPhys : 1;
	port_info->phy_info = kcalloc(port_info->num_phys,
	    sizeof(struct mptsas_phyinfo), GFP_KERNEL);
	if (!port_info->phy_info)
		BUG();
	memcpy(&sas_address, &expander_data->SASAddress, sizeof(__le64));
	for (i = 0; i < port_info->num_phys; i++) {
		port_info->phy_info[i].portinfo = port_info;
		port_info->phy_info[i].handle =
		    le16_to_cpu(expander_data->DevHandle);
		port_info->phy_info[i].identify.sas_address =
		    le64_to_cpu(sas_address);
		port_info->phy_info[i].identify.handle_parent =
		    le16_to_cpu(expander_data->ParentDevHandle);
	}

	mutex_lock(&ioc->sas_topology_mutex);
	list_add_tail(&port_info->list, &ioc->sas_topology);
	mutex_unlock(&ioc->sas_topology_mutex);

	printk(MYIOC_s_INFO_FMT "add expander: num_phys %d, "
	    "sas_addr (0x%llx)\n", ioc->name, port_info->num_phys,
	    (unsigned long long)sas_address);

	mptsas_expander_refresh(ioc, port_info);
}
