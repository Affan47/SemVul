pvr2_try_fmt_vid_cap(struct file *file, void *priv, struct v4l2_format *vf)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	int lmin, lmax, ldef;
	struct pvr2_ctrl *hcp, *vcp;
	int h = vf->fmt.pix.height;
	int w = vf->fmt.pix.width;

	hcp = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_HRES);
	vcp = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_VRES);

	lmin = pvr2_ctrl_get_min(hcp);
	lmax = pvr2_ctrl_get_max(hcp);
	pvr2_ctrl_get_def(hcp, &ldef);
	if (w == -1)
		w = ldef;
	else if (w < lmin)
		w = lmin;
	else if (w > lmax)
		w = lmax;
	lmin = pvr2_ctrl_get_min(vcp);
	lmax = pvr2_ctrl_get_max(vcp);
	pvr2_ctrl_get_def(vcp, &ldef);
	if (h == -1)
		h = ldef;
	else if (h < lmin)
		h = lmin;
	else if (h > lmax)
		h = lmax;

	memcpy(vf, &pvr_format[PVR_FORMAT_PIX],
			sizeof(struct v4l2_format));
	vf->fmt.pix.width = w;
	vf->fmt.pix.height = h;
	return 0;
}
