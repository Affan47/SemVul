get_data(void **data_ptr, int data_requested)
{
	int len;
	audio_buf_info info;

	int err = ioctl(dev_dsp_fd, SNDCTL_DSP_GETISPACE, &info);
	if (err == -1)
	{
		CL_Log::log("debug", "ClanSound: fragments free not supported by device!?");
		position = 0;
	}
	if(info.fragments == 0)
	{
		return 0;
	}
	else
	{
		len = read(dev_dsp_fd, data_ptr[0], data_requested);
	}

	position += len;
	return position;
}
