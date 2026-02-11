get_inf_dev_status(struct v4l2_subdev *sd,
		int *dual_flag, int *stereo_flag)
{
	u32 reg_data3;

	static char *stdres[0x20] = {
		[0x00] = "no standard detected",
		[0x01] = "B/G (in progress)",
		[0x02] = "D/K (in progress)",
		[0x03] = "M (in progress)",

		[0x04] = "B/G A2",
		[0x05] = "B/G NICAM",
		[0x06] = "D/K A2 (1)",
		[0x07] = "D/K A2 (2)",
		[0x08] = "D/K A2 (3)",
		[0x09] = "D/K NICAM",
		[0x0a] = "L NICAM",
		[0x0b] = "I NICAM",

		[0x0c] = "M Korea",
		[0x0d] = "M BTSC ",
		[0x0e] = "M EIAJ",

		[0x0f] = "FM radio / IF 10.7 / 50 deemp",
		[0x10] = "FM radio / IF 10.7 / 75 deemp",
		[0x11] = "FM radio / IF sel / 50 deemp",
		[0x12] = "FM radio / IF sel / 75 deemp",

		[0x13 ... 0x1e] = "unknown",
		[0x1f] = "??? [in progress]",
	};


	*dual_flag = *stereo_flag = 0;


	reg_data3 = saa717x_read(sd, 0x0528);

	v4l2_dbg(1, debug, sd, "tvaudio thread status: 0x%x [%s%s%s]\n",
		reg_data3, stdres[reg_data3 & 0x1f],
		(reg_data3 & 0x000020) ? ",stereo" : "",
		(reg_data3 & 0x000040) ? ",dual"   : "");
	v4l2_dbg(1, debug, sd, "detailed status: "
		"%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s\n",
		(reg_data3 & 0x000080) ? " A2/EIAJ pilot tone "     : "",
		(reg_data3 & 0x000100) ? " A2/EIAJ dual "           : "",
		(reg_data3 & 0x000200) ? " A2/EIAJ stereo "         : "",
		(reg_data3 & 0x000400) ? " A2/EIAJ noise mute "     : "",

		(reg_data3 & 0x000800) ? " BTSC/FM radio pilot "    : "",
		(reg_data3 & 0x001000) ? " SAP carrier "            : "",
		(reg_data3 & 0x002000) ? " BTSC stereo noise mute " : "",
		(reg_data3 & 0x004000) ? " SAP noise mute "         : "",
		(reg_data3 & 0x008000) ? " VDSP "                   : "",

		(reg_data3 & 0x010000) ? " NICST "                  : "",
		(reg_data3 & 0x020000) ? " NICDU "                  : "",
		(reg_data3 & 0x040000) ? " NICAM muted "            : "",
		(reg_data3 & 0x080000) ? " NICAM reserve sound "    : "",

		(reg_data3 & 0x100000) ? " init done "              : "");

	if (reg_data3 & 0x000220) {
		v4l2_dbg(1, debug, sd, "ST!!!\n");
		*stereo_flag = 1;
	}

	if (reg_data3 & 0x000140) {
		v4l2_dbg(1, debug, sd, "DUAL!!!\n");
		*dual_flag = 1;
	}
}
