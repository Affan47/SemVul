fm10k_tlv_attr_nest_stop(u32 *msg)
{
	u32 *attr;
	u32 len;


	if (!msg)
		return FM10K_ERR_PARAM;


	attr = &msg[FM10K_TLV_DWORD_LEN(*msg)];
	len = (attr[0] >> FM10K_TLV_LEN_SHIFT) << FM10K_TLV_LEN_SHIFT;


	if (len) {
		len += FM10K_TLV_HDR_LEN << FM10K_TLV_LEN_SHIFT;
		*msg += len;
	}

	return 0;
}
