static u8 dccp_feat_valid_nn_length(u8 feat_num)
{
	if (feat_num == DCCPF_ACK_RATIO)
		return 2;
	if (feat_num == DCCPF_SEQUENCE_WINDOW)
		return 6;
	return 0;
}
