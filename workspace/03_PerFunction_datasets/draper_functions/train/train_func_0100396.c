qlcnic_sriov_handle_msg_event(struct qlcnic_sriov *sriov,
					  struct qlcnic_vf_info *vf)
{
	struct qlcnic_bc_hdr hdr;
	u32 *ptr = (u32 *)&hdr;
	u8 msg_type, i;

	for (i = 2; i < 6; i++)
		ptr[i - 2] = readl(QLCNIC_MBX_FW(vf->adapter->ahw, i));
	msg_type = hdr.msg_type;

	switch (msg_type) {
	case QLC_BC_COMMAND:
		qlcnic_sriov_handle_bc_cmd(sriov, &hdr, vf);
		break;
	case QLC_BC_RESPONSE:
		qlcnic_sriov_handle_bc_resp(&hdr, vf);
		break;
	}
}
