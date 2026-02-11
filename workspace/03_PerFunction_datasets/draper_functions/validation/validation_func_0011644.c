esas2r_disc_passthru_dev_info_cb(struct esas2r_adapter *a,
					     struct esas2r_request *rq)
{
	struct esas2r_disc_context *dc =
		(struct esas2r_disc_context *)rq->interrupt_cx;
	unsigned long flags;
	struct atto_vda_devinfo *devinfo;

	esas2r_trace_enter();

	spin_lock_irqsave(&a->mem_lock, flags);

	if (rq->req_stat == RS_SCAN_GEN) {
		dc->scan_gen = rq->func_rsp.mgt_rsp.scan_generation;
		dc->dev_ix = 0;
		dc->state = DCS_PT_DEV_INFO;
	} else if (rq->req_stat == RS_SUCCESS) {
		devinfo = &rq->vda_rsp_data->mgt_data.data.dev_info;

		dc->dev_ix = le16_to_cpu(rq->func_rsp.mgt_rsp.dev_index);

		dc->curr_virt_id = le16_to_cpu(devinfo->target_id);

		if (le16_to_cpu(devinfo->features) & VDADEVFEAT_PHYS_ID) {
			dc->curr_phys_id =
				le16_to_cpu(devinfo->phys_target_id);
			dc->dev_addr_type = ATTO_GDA_AT_PORT;
			dc->state = DCS_PT_DEV_ADDR;

			esas2r_trace("curr_virt_id: %d", dc->curr_virt_id);
			esas2r_trace("curr_phys_id: %d", dc->curr_phys_id);
		} else {
			dc->dev_ix++;
		}
	} else {
		if (!(rq->req_stat == RS_DEV_INVALID)) {
			esas2r_log(ESAS2R_LOG_WARN,
				   "A request for device information failed - "
				   "status:%d", rq->req_stat);
		}

		dc->state = DCS_DISC_DONE;
	}

	esas2r_rq_destroy_request(rq, a);


	if (!(dc->flags & DCF_POLLED))
		esas2r_disc_continue(a, rq);

	spin_unlock_irqrestore(&a->mem_lock, flags);

	esas2r_trace_exit();
}
