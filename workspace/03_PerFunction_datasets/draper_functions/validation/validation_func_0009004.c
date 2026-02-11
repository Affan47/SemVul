st6422_start(struct sd *sd)
{
	int err;
	struct cam *cam = &sd->gspca_dev.cam;

	if (cam->cam_mode[sd->gspca_dev.curr_mode].priv)
		err = stv06xx_write_bridge(sd, 0x1505, 0x0f);
	else
		err = stv06xx_write_bridge(sd, 0x1505, 0x02);
	if (err < 0)
		return err;


	err = stv06xx_write_bridge(sd, 0x143f, 0x01);
	return (err < 0) ? err : 0;
}
