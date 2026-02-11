hfi1_make_ruc_header(struct hfi1_qp *qp, struct hfi1_other_headers *ohdr,
			  u32 bth0, u32 bth2, int middle)
{
	struct hfi1_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	u16 lrh0;
	u32 nwords;
	u32 extra_bytes;
	u8 sc5;
	u32 bth1;


	extra_bytes = -qp->s_cur_size & 3;
	nwords = (qp->s_cur_size + extra_bytes) >> 2;
	lrh0 = HFI1_LRH_BTH;
	if (unlikely(qp->remote_ah_attr.ah_flags & IB_AH_GRH)) {
		qp->s_hdrwords += hfi1_make_grh(ibp, &qp->s_hdr->ibh.u.l.grh,
					       &qp->remote_ah_attr.grh,
					       qp->s_hdrwords, nwords);
		lrh0 = HFI1_LRH_GRH;
		middle = 0;
	}
	sc5 = ibp->sl_to_sc[qp->remote_ah_attr.sl];
	lrh0 |= (sc5 & 0xf) << 12 | (qp->remote_ah_attr.sl & 0xf) << 4;
	qp->s_sc = sc5;


	qp->s_hdr->tx_flags = 0;
	qp->s_hdr->ahgcount = 0;
	qp->s_hdr->ahgidx = 0;
	qp->s_hdr->sde = NULL;
	if (qp->s_mig_state == IB_MIG_MIGRATED)
		bth0 |= IB_BTH_MIG_REQ;
	else
		middle = 0;
	if (middle)
		build_ahg(qp, bth2);
	else
		qp->s_flags &= ~HFI1_S_AHG_VALID;
	qp->s_hdr->ibh.lrh[0] = cpu_to_be16(lrh0);
	qp->s_hdr->ibh.lrh[1] = cpu_to_be16(qp->remote_ah_attr.dlid);
	qp->s_hdr->ibh.lrh[2] =
		cpu_to_be16(qp->s_hdrwords + nwords + SIZE_OF_CRC);
	qp->s_hdr->ibh.lrh[3] = cpu_to_be16(ppd_from_ibp(ibp)->lid |
				       qp->remote_ah_attr.src_path_bits);
	bth0 |= hfi1_get_pkey(ibp, qp->s_pkey_index);
	bth0 |= extra_bytes << 20;
	ohdr->bth[0] = cpu_to_be32(bth0);
	bth1 = qp->remote_qpn;
	if (qp->s_flags & HFI1_S_ECN) {
		qp->s_flags &= ~HFI1_S_ECN;

		bth1 |= (HFI1_BECN_MASK << HFI1_BECN_SHIFT);
	}
	ohdr->bth[1] = cpu_to_be32(bth1);
	ohdr->bth[2] = cpu_to_be32(bth2);
}
