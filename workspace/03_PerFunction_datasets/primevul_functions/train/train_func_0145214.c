static int dccp_feat_default_value(u8 feat_num)
{
	int idx = dccp_feat_index(feat_num);


	DCCP_BUG_ON(idx < 0);

	return idx < 0 ? 0 : dccp_feat_table[idx].default_value;
}
