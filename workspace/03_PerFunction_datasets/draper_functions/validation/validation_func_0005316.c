qed_init_rt(struct qed_hwfn *p_hwfn,
			struct qed_ptt *p_ptt,
			u32 addr,
			u32 rt_offset,
			u32 size)
{
	struct qed_rt_data *rt_data = p_hwfn->rt_data + rt_offset;
	u32 i;

	for (i = 0; i < size; i++) {
		if (!rt_data[i].b_valid)
			continue;
		qed_wr(p_hwfn, p_ptt, addr + (i << 2), rt_data[i].init_val);
	}
}
