static void i40e_vsi_setup_queue_map(struct i40e_vsi *vsi,
				     struct i40e_vsi_context *ctxt,
				     u8 enabled_tc,
				     bool is_add)
{
	struct i40e_pf *pf = vsi->back;
	u16 sections = 0;
	u8 netdev_tc = 0;
	u16 numtc = 1;
	u16 qcount;
	u8 offset;
	u16 qmap;
	int i;
	u16 num_tc_qps = 0;

	sections = I40E_AQ_VSI_PROP_QUEUE_MAP_VALID;
	offset = 0;


	num_tc_qps = vsi->alloc_queue_pairs;
	if (enabled_tc && (vsi->back->flags & I40E_FLAG_DCB_ENABLED)) {

		for (i = 0, numtc = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) {
			if (enabled_tc & BIT(i))
				numtc++;
		}
		if (!numtc) {
			dev_warn(&pf->pdev->dev, "DCB is enabled but no TC enabled, forcing TC0\n");
			numtc = 1;
		}
		num_tc_qps = num_tc_qps / numtc;
		num_tc_qps = min_t(int, num_tc_qps,
				   i40e_pf_get_max_q_per_tc(pf));
	}

	vsi->tc_config.numtc = numtc;
	vsi->tc_config.enabled_tc = enabled_tc ? enabled_tc : 1;


	if (pf->flags & I40E_FLAG_MSIX_ENABLED)
		num_tc_qps = min_t(int, num_tc_qps, pf->num_lan_msix);


	for (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) {

		if (vsi->tc_config.enabled_tc & BIT(i)) {

			int pow, num_qps;

			switch (vsi->type) {
			case I40E_VSI_MAIN:
				if (!(pf->flags & (I40E_FLAG_FD_SB_ENABLED |
				    I40E_FLAG_FD_ATR_ENABLED)) ||
				    vsi->tc_config.enabled_tc != 1) {
					qcount = min_t(int, pf->alloc_rss_size,
						       num_tc_qps);
					break;
				}

			case I40E_VSI_FDIR:
			case I40E_VSI_SRIOV:
			case I40E_VSI_VMDQ2:
			default:
				qcount = num_tc_qps;
				WARN_ON(i != 0);
				break;
			}
			vsi->tc_config.tc_info[i].qoffset = offset;
			vsi->tc_config.tc_info[i].qcount = qcount;


			num_qps = qcount;
			pow = 0;
			while (num_qps && (BIT_ULL(pow) < qcount)) {
				pow++;
				num_qps >>= 1;
			}

			vsi->tc_config.tc_info[i].netdev_tc = netdev_tc++;
			qmap =
			    (offset << I40E_AQ_VSI_TC_QUE_OFFSET_SHIFT) |
			    (pow << I40E_AQ_VSI_TC_QUE_NUMBER_SHIFT);

			offset += qcount;
		} else {


			vsi->tc_config.tc_info[i].qoffset = 0;
			vsi->tc_config.tc_info[i].qcount = 1;
			vsi->tc_config.tc_info[i].netdev_tc = 0;

			qmap = 0;
		}
		ctxt->info.tc_mapping[i] = cpu_to_le16(qmap);
	}


	vsi->num_queue_pairs = offset;
	if ((vsi->type == I40E_VSI_MAIN) && (numtc == 1)) {
		if (vsi->req_queue_pairs > 0)
			vsi->num_queue_pairs = vsi->req_queue_pairs;
		else if (pf->flags & I40E_FLAG_MSIX_ENABLED)
			vsi->num_queue_pairs = pf->num_lan_msix;
	}


	if (is_add) {
		sections |= I40E_AQ_VSI_PROP_SCHED_VALID;

		ctxt->info.up_enable_bits = enabled_tc;
	}
	if (vsi->type == I40E_VSI_SRIOV) {
		ctxt->info.mapping_flags |=
				     cpu_to_le16(I40E_AQ_VSI_QUE_MAP_NONCONTIG);
		for (i = 0; i < vsi->num_queue_pairs; i++)
			ctxt->info.queue_mapping[i] =
					       cpu_to_le16(vsi->base_queue + i);
	} else {
		ctxt->info.mapping_flags |=
					cpu_to_le16(I40E_AQ_VSI_QUE_MAP_CONTIG);
		ctxt->info.queue_mapping[0] = cpu_to_le16(vsi->base_queue);
	}
	ctxt->info.valid_sections |= cpu_to_le16(sections);
}
