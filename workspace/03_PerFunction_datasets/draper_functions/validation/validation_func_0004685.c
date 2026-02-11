uwb_drp_process_target(struct uwb_rc *rc, struct uwb_rsv *rsv,
		   struct uwb_ie_drp *drp_ie, struct uwb_rc_evt_drp *drp_evt)
{
	struct device *dev = &rc->uwb_dev.dev;
	struct uwb_rsv_move *mv = &rsv->mv;
	int status;
	enum uwb_drp_reason reason_code;
	struct uwb_mas_bm mas;

	status = uwb_ie_drp_status(drp_ie);
	reason_code = uwb_ie_drp_reason_code(drp_ie);
	uwb_drp_ie_to_bm(&mas, drp_ie);

	switch (reason_code) {
	case UWB_DRP_REASON_ACCEPTED:
		uwb_drp_process_target_accepted(rc, rsv, drp_evt, drp_ie, &mas);
		break;

	case UWB_DRP_REASON_MODIFIED:

		if (bitmap_equal(rsv->mas.bm, mas.bm, UWB_NUM_MAS)) {
			uwb_rsv_set_state(rsv, UWB_RSV_STATE_T_ACCEPTED);
			break;
		}


		if (bitmap_subset(mas.bm, rsv->mas.bm, UWB_NUM_MAS)) {

			bitmap_andnot(mv->companion_mas.bm, rsv->mas.bm, mas.bm,
				UWB_NUM_MAS);
			uwb_drp_avail_release(rsv->rc, &mv->companion_mas);
		}

		bitmap_copy(rsv->mas.bm, mas.bm, UWB_NUM_MAS);
		uwb_rsv_set_state(rsv, UWB_RSV_STATE_T_RESIZED);
		break;
	default:
		dev_warn(dev, "ignoring invalid DRP IE state (%d/%d)\n",
			 reason_code, status);
	}
}
