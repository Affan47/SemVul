qlcnic_82xx_dcb_get_cee_cfg(struct qlcnic_dcb *dcb)
{
	struct qlcnic_dcb_mbx_params *mbx;
	int err;

	mbx = dcb->param;
	if (!mbx)
		return 0;

	err = qlcnic_dcb_query_cee_param(dcb, (char *)&mbx->type[0],
					 QLC_DCB_LOCAL_PARAM_FWID);
	if (err)
		return err;

	err = qlcnic_dcb_query_cee_param(dcb, (char *)&mbx->type[1],
					 QLC_DCB_OPER_PARAM_FWID);
	if (err)
		return err;

	err = qlcnic_dcb_query_cee_param(dcb, (char *)&mbx->type[2],
					 QLC_DCB_PEER_PARAM_FWID);
	if (err)
		return err;

	mbx->prio_tc_map = QLC_82XX_DCB_PRIO_TC_MAP;

	qlcnic_dcb_data_cee_param_map(dcb->adapter);

	return err;
}
