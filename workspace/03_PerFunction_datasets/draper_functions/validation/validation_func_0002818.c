pvr2_subdev_set_control(struct pvr2_hdw *hdw, int id,
				    const char *name, int val)
{
	struct v4l2_control ctrl;
	pvr2_trace(PVR2_TRACE_CHIPS, "subdev v4l2 %s=%d", name, val);
	memset(&ctrl, 0, sizeof(ctrl));
	ctrl.id = id;
	ctrl.value = val;
	v4l2_device_call_all(&hdw->v4l2_dev, 0, core, s_ctrl, &ctrl);
}
