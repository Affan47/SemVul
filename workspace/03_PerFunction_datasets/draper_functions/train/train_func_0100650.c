niu_get_ethtool_tcam_entry(struct niu *np,
				      struct ethtool_rxnfc *nfc)
{
	struct niu_parent *parent = np->parent;
	struct niu_tcam_entry *tp;
	struct ethtool_rx_flow_spec *fsp = &nfc->fs;
	u16 idx;
	u64 class;
	int ret = 0;

	idx = tcam_get_index(np, (u16)nfc->fs.location);

	tp = &parent->tcam[idx];
	if (!tp->valid) {
		netdev_info(np->dev, "niu%d: entry [%d] invalid for idx[%d]\n",
			    parent->index, (u16)nfc->fs.location, idx);
		return -EINVAL;
	}


	class = (tp->key[0] & TCAM_V4KEY0_CLASS_CODE) >>
		TCAM_V4KEY0_CLASS_CODE_SHIFT;
	ret = niu_class_to_ethflow(class, &fsp->flow_type);
	if (ret < 0) {
		netdev_info(np->dev, "niu%d: niu_class_to_ethflow failed\n",
			    parent->index);
		goto out;
	}

	if (fsp->flow_type == AH_V4_FLOW || fsp->flow_type == AH_V6_FLOW) {
		u32 proto = (tp->key[2] & TCAM_V4KEY2_PROTO) >>
			TCAM_V4KEY2_PROTO_SHIFT;
		if (proto == IPPROTO_ESP) {
			if (fsp->flow_type == AH_V4_FLOW)
				fsp->flow_type = ESP_V4_FLOW;
			else
				fsp->flow_type = ESP_V6_FLOW;
		}
	}

	switch (fsp->flow_type) {
	case TCP_V4_FLOW:
	case UDP_V4_FLOW:
	case SCTP_V4_FLOW:
	case AH_V4_FLOW:
	case ESP_V4_FLOW:
		niu_get_ip4fs_from_tcam_key(tp, fsp);
		break;
	case TCP_V6_FLOW:
	case UDP_V6_FLOW:
	case SCTP_V6_FLOW:
	case AH_V6_FLOW:
	case ESP_V6_FLOW:

		ret = -EINVAL;
		break;
	case IP_USER_FLOW:
		niu_get_ip4fs_from_tcam_key(tp, fsp);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (ret < 0)
		goto out;

	if (tp->assoc_data & TCAM_ASSOCDATA_DISC)
		fsp->ring_cookie = RX_CLS_FLOW_DISC;
	else
		fsp->ring_cookie = (tp->assoc_data & TCAM_ASSOCDATA_OFFSET) >>
			TCAM_ASSOCDATA_OFFSET_SHIFT;


	nfc->data = tcam_get_size(np);
out:
	return ret;
}
