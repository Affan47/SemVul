modify_qp_mask(enum ib_qp_type qp_type, int mask)
{
	switch (qp_type) {
	case IB_QPT_XRC_INI:
		return mask & ~(IB_QP_MAX_DEST_RD_ATOMIC | IB_QP_MIN_RNR_TIMER);
	case IB_QPT_XRC_TGT:
		return mask & ~(IB_QP_MAX_QP_RD_ATOMIC | IB_QP_RETRY_CNT |
				IB_QP_RNR_RETRY);
	default:
		return mask;
	}
}
