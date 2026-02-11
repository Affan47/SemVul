hpi_channel_mode_get(u32 h_control, u16 *mode)
{
	u32 mode32 = 0;
	u16 err = hpi_control_param1_get(h_control,
		HPI_CHANNEL_MODE_MODE, &mode32);
	if (mode)
		*mode = (u16)mode32;
	return err;
}
