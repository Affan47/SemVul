qed_qm_pf_mem_size(u8 pf_id,
		       u32 num_pf_cids,
		       u32 num_vf_cids,
		       u32 num_tids,
		       u16 num_pf_pqs,
		       u16 num_vf_pqs)
{
	return QM_PQ_MEM_4KB(num_pf_cids) * num_pf_pqs +
	       QM_PQ_MEM_4KB(num_vf_cids) * num_vf_pqs +
	       QM_PQ_MEM_4KB(num_pf_cids + num_tids) * QM_OTHER_PQS_PER_PF;
}
