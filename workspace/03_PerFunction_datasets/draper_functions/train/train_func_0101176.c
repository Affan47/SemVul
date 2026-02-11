bnx2fc_split_bd(struct bnx2fc_cmd *io_req, u64 addr, int sg_len,
			   int bd_index)
{
	struct fcoe_bd_ctx *bd = io_req->bd_tbl->bd_tbl;
	int frag_size, sg_frags;

	sg_frags = 0;
	while (sg_len) {
		if (sg_len >= BNX2FC_BD_SPLIT_SZ)
			frag_size = BNX2FC_BD_SPLIT_SZ;
		else
			frag_size = sg_len;
		bd[bd_index + sg_frags].buf_addr_lo = addr & 0xffffffff;
		bd[bd_index + sg_frags].buf_addr_hi  = addr >> 32;
		bd[bd_index + sg_frags].buf_len = (u16)frag_size;
		bd[bd_index + sg_frags].flags = 0;

		addr += (u64) frag_size;
		sg_frags++;
		sg_len -= frag_size;
	}
	return sg_frags;

}
