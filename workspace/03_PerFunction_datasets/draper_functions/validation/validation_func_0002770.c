bnxt_set_vf_link_state(struct net_device *dev, int vf_id, int link)
{
	struct bnxt *bp = netdev_priv(dev);
	struct bnxt_vf_info *vf;
	int rc;

	rc = bnxt_vf_ndo_prep(bp, vf_id);
	if (rc)
		return rc;

	vf = &bp->pf.vf[vf_id];

	vf->flags &= ~(BNXT_VF_LINK_UP | BNXT_VF_LINK_FORCED);
	switch (link) {
	case IFLA_VF_LINK_STATE_AUTO:
		vf->flags |= BNXT_VF_LINK_UP;
		break;
	case IFLA_VF_LINK_STATE_DISABLE:
		vf->flags |= BNXT_VF_LINK_FORCED;
		break;
	case IFLA_VF_LINK_STATE_ENABLE:
		vf->flags |= BNXT_VF_LINK_UP | BNXT_VF_LINK_FORCED;
		break;
	default:
		netdev_err(bp->dev, "Invalid link option\n");
		rc = -EINVAL;
		break;
	}


	return rc;
}
