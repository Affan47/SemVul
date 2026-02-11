sd_init_controls(struct gspca_dev *gspca_dev)
{
	struct v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;
	struct sd *sd = (struct sd *)gspca_dev;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 2);

	switch (sd->model) {
	case 0x7003:
		sd->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_GAIN, 0, 20, 1, 0);
		sd->autogain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
		break;
	default:
		break;
	}

	return 0;
}
