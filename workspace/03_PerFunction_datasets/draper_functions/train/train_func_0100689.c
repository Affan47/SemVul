transmit_linestatres(struct skinny_device *d, int instance)
{
	struct skinny_req *req;
	struct skinny_line *l;
	struct skinny_speeddial *sd;

	if (!(req = req_alloc(sizeof(struct line_stat_res_message), LINE_STAT_RES_MESSAGE)))
		return;

	if ((l = find_line_by_instance(d, instance))) {
		req->data.linestat.lineNumber = letohl(l->instance);
		memcpy(req->data.linestat.lineDirNumber, l->name, sizeof(req->data.linestat.lineDirNumber));
		memcpy(req->data.linestat.lineDisplayName, l->label, sizeof(req->data.linestat.lineDisplayName));
	} else if ((sd = find_speeddial_by_instance(d, instance, 1))) {
		req->data.linestat.lineNumber = letohl(sd->instance);
		memcpy(req->data.linestat.lineDirNumber, sd->label, sizeof(req->data.linestat.lineDirNumber));
		memcpy(req->data.linestat.lineDisplayName, sd->label, sizeof(req->data.linestat.lineDisplayName));
	}

	SKINNY_DEBUG(DEBUG_PACKET, 3, "Transmitting LINE_STAT_RES_MESSAGE to %s, inst %d, num %s, label %s\n",
		d->name, l->instance, req->data.linestat.lineDirNumber, req->data.linestat.lineDisplayName);
	transmit_response(d, req);
}
