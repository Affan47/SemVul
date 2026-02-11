netxen_init_firmware(struct netxen_adapter *adapter)
{
	int err;

	err = netxen_receive_peg_ready(adapter);
	if (err)
		return err;

	NXWR32(adapter, CRB_NIC_CAPABILITIES_HOST, INTR_SCHEME_PERPORT);
	NXWR32(adapter, CRB_MPORT_MODE, MPORT_MULTI_FUNCTION_MODE);
	NXWR32(adapter, CRB_CMDPEG_STATE, PHAN_INITIALIZE_ACK);

	if (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		NXWR32(adapter, CRB_NIC_MSI_MODE_HOST, MSI_MODE_MULTIFUNC);

	return err;
}
