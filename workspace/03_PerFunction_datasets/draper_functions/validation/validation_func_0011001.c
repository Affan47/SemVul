bnx2x_lock_vf_pf_channel(struct bnx2x *bp, struct bnx2x_virtf *vf,
			      enum channel_tlvs tlv)
{

	if (!bnx2x_tlv_supported(tlv)) {
		BNX2X_ERR("attempting to lock with unsupported tlv. Aborting\n");
		return;
	}


	mutex_lock(&vf->op_mutex);


	vf->op_current = tlv;


	DP(BNX2X_MSG_IOV, "VF[%d]: vf pf channel locked by %d\n",
	   vf->abs_vfid, tlv);
}
