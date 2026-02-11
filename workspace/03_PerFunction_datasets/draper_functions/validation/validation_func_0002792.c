__subn_get_opa_cc_table(struct opa_smp *smp, u32 am, u8 *data,
				   struct ib_device *ibdev, u8 port,
				   u32 *resp_len)
{
	struct ib_cc_table_attr *cc_table_attr =
		(struct ib_cc_table_attr *) data;
	struct hfi1_ibport *ibp = to_iport(ibdev, port);
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u32 start_block = OPA_AM_START_BLK(am);
	u32 n_blocks = OPA_AM_NBLK(am);
	struct ib_cc_table_entry_shadow *entries;
	int i, j;
	u32 sentry, eentry;
	struct cc_state *cc_state;


	if (n_blocks == 0 ||
	    start_block + n_blocks > ppd->cc_max_table_entries) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	rcu_read_lock();

	cc_state = get_cc_state(ppd);

	if (cc_state == NULL) {
		rcu_read_unlock();
		return reply((struct ib_mad_hdr *)smp);
	}

	sentry = start_block * IB_CCT_ENTRIES;
	eentry = sentry + (IB_CCT_ENTRIES * n_blocks);

	cc_table_attr->ccti_limit = cpu_to_be16(cc_state->cct.ccti_limit);

	entries = cc_state->cct.entries;


	for (j = 0, i = sentry; i < eentry; j++, i++)
		cc_table_attr->ccti_entries[j].entry =
			cpu_to_be16(entries[i].entry);

	rcu_read_unlock();

	if (resp_len)
		*resp_len += sizeof(u16)*(IB_CCT_ENTRIES * n_blocks + 1);

	return reply((struct ib_mad_hdr *)smp);
}
