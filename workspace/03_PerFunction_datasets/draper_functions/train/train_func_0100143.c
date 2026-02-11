dwc2_complete_non_isoc_xfer_ddma(struct dwc2_hsotg *hsotg,
					     struct dwc2_host_chan *chan,
					     int chnum,
					     enum dwc2_halt_status halt_status)
{
	struct list_head *qtd_item, *qtd_tmp;
	struct dwc2_qh *qh = chan->qh;
	struct dwc2_qtd *qtd = NULL;
	int xfer_done;
	int desc_num = 0;

	if (chan->halt_status == DWC2_HC_XFER_URB_DEQUEUE) {
		list_for_each_entry(qtd, &qh->qtd_list, qtd_list_entry)
			qtd->in_process = 0;
		return;
	}

	list_for_each_safe(qtd_item, qtd_tmp, &qh->qtd_list) {
		int i;

		qtd = list_entry(qtd_item, struct dwc2_qtd, qtd_list_entry);
		xfer_done = 0;

		for (i = 0; i < qtd->n_desc; i++) {
			if (dwc2_process_non_isoc_desc(hsotg, chan, chnum, qtd,
						       desc_num, halt_status,
						       &xfer_done)) {
				qtd = NULL;
				break;
			}
			desc_num++;
		}
	}

	if (qh->ep_type != USB_ENDPOINT_XFER_CONTROL) {


		if (halt_status == DWC2_HC_XFER_STALL)
			qh->data_toggle = DWC2_HC_PID_DATA0;
		else if (qtd)
			dwc2_hcd_save_data_toggle(hsotg, chan, chnum, qtd);
	}

	if (halt_status == DWC2_HC_XFER_COMPLETE) {
		if (chan->hcint & HCINTMSK_NYET) {


			qh->ping_state = 1;
		}
	}
}
